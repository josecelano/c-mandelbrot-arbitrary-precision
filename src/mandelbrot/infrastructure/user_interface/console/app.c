#include <argp.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../../application/config.h"
#include "../../../domain/ascii_graph/ascii_graph.h"
#include "../../../domain/ascii_graph/ascii_map.h"
#include "../../../domain/fractal.h"
#include "../../../domain/image/color_map.h"
#include "../../../domain/set.h"
#include "../../../domain/ztile.h"
#include "../../../infrastructure/user_interface/files/ascii_graph_file.h"
#include "../../../infrastructure/user_interface/files/ppm_image_file.h"
#include "../../../presentation/output.h"
#include "./app.h"

/*
 * TODO: WIP. Only verbose options are obtained from console arguments.
 *
 * CONSOLE COMMAND:
 * mandelbrot [Z_CENTER_X] [Z_CENTER_Y] [Z_WIDTH] [Z_HEIGHT] [RES_X] [RES_Y] [FORMAT] [COLOR_MAP|ASCII_MAP] [FILENAME]
 *
 * IMAGE:
 * mandelbrot -2 -2 4 4 256 256 0 0 ./output/mandelbrot-black-on-white-256x256.ppm
 *
 * ASCII GRAPH:
 * mandelbrot -2 -2 4 4 256 256 0 0 ./output/mandelbrot-at-sign-256x256.txt
 */

const char *argp_program_version = "mandelbrot 1.0.0";
const char *argp_program_bug_address = "https://github.com/josecelano/c-mandelbrot-arbitrary-precision/issues";
static char doc[] = "Mandelbrot Set image and ASCII graph generator.";
static char args_doc[] = "[RES_X]... [RES_Y]... [FORMAT]... [COLOR_MAP|ASCII_MAP]...";
static struct argp_option options[] = {
        // Verbose options
        {"print_progress",          'p', 0, 0, "Verbose opt: Print progress"},
        {"print_periods",           'e', 0, 0, "Verbose opt: Print periods"},
        {"print_iterations",        't', 0, 0, "Verbose opt: Print iterations"},
        {"print_performance_data",  'r', 0, 0, "Verbose opt: Print performance data"},
        {"print_fractal_data",      'f', 0, 0, "Verbose opt: Print fractal data"},
        // Optimisation options
        {"main_cardioid_detection", 'c', 0, 0, "Optimisation opt: Main cardioid detection"},
        {"period2_detection",       'o', 0, 0, "Optimisation opt: Period 2 detection"},
        {"periodicity_checking",    'y', 0, 0, "Optimisation opt: Periodicity checking"},
        // Dev extras
        {"generate_all_samples",    'A', 0, 0, "Generate samples with all color/ascii maps"},
        {0}
};

struct arguments {
    config_t *config;
    resolution_t *resolution;
    enum {
        FORMAT_PPM = 0,
        FORMAT_ASCII_GRAPH = 1
    } format;
    color_map_t color_map;
    ascii_map_t ascii_map;
    int generate_all_samples;
};

static error_t parse_opt(int key, char *arg, struct argp_state *state) {
    struct arguments *arguments = state->input;
    switch (key) {

        case 'p':
            app_config_enable_verbose_option(arguments->config, VO_PRINT_PROGRESS);
            break;
        case 'e':
            app_config_enable_verbose_option(arguments->config, VO_PRINT_PERIODS);
            break;
        case 't':
            app_config_enable_verbose_option(arguments->config, VO_PRINT_ITERATIONS);
            break;
        case 'r':
            app_config_enable_verbose_option(arguments->config, VO_PRINT_PERFORMANCE_DATA);
            break;
        case 'f':
            app_config_enable_verbose_option(arguments->config, VO_PRINT_FRACTAL_DATA);
            break;

        case 'c':
            app_config_optimisation_option_enabled(arguments->config, OO_MAIN_CARDIOID_DETECTION);
            break;
        case 'o':
            app_config_optimisation_option_enabled(arguments->config, OO_PERIOD2_DETECTION);
            break;
        case 'y':
            app_config_optimisation_option_enabled(arguments->config, OO_PERIODICITY_CHECKING);
            break;

        case 'A':
            arguments->generate_all_samples = 1;
            break;

        case ARGP_KEY_ARG:
            switch (state->arg_num) {
                case 0: // RES_X
                    arguments->resolution->width = atoi(arg);
                    break;
                case 1: // RES_Y
                    arguments->resolution->height = atoi(arg);
                    break;
                case 2: // FORMAT
                    arguments->format = atoi(arg);
                    break;
                case 3: // COLOR_MAP | ASCII_MAP
                    if (arguments->format == FORMAT_PPM) {
                        arguments->color_map = atoi(arg);
                    }
                    if (arguments->format == FORMAT_ASCII_GRAPH) {
                        arguments->ascii_map = atoi(arg);
                    }
                    break;
            }
            break;
        default:
            return ARGP_ERR_UNKNOWN;
    }
    return 0;
}

static struct argp argp = {options, parse_opt, args_doc, doc, 0, 0, 0};

void render_ppm_image(fractal_data_t fractal_data, color_map_t color_map) {
    char color_map_name[50];
    char img_filename[50];

    get_color_map_name(color_map_name, color_map);

    sprintf(img_filename, "./output/mandelbrot-%s-%dx%d.ppm",
            color_map_name,
            fractal_data.resolution.width,
            fractal_data.resolution.height
    );

    render_and_write_out_image(img_filename, fractal_data, color_map);
}

void render_ascii_graph(fractal_data_t fractal_data, ascii_map_t ascii_map) {
    char ascii_map_name[50];
    char img_filename[50];

    get_ascii_map_name(ascii_map_name, ascii_map);

    sprintf(img_filename, "./output/mandelbrot-%s-%dx%d.txt",
            ascii_map_name,
            fractal_data.resolution.width,
            fractal_data.resolution.height
    );

    render_fractal_and_write_out_the_text_file(img_filename, fractal_data, ascii_map);
}

void generate_all_samples(fractal_data_t fractal_data) {
    // Render images
    render_ppm_image(fractal_data, CM_BLACK_ON_WHITE);
    render_ppm_image(fractal_data, CM_WHITE_ON_BLACK);
    render_ppm_image(fractal_data, CM_COLORED_PERIODS);

    // Render ascii graphs
    render_ascii_graph(fractal_data, AM_AT_SIGN);
    render_ascii_graph(fractal_data, AM_ITERATIONS);
    render_ascii_graph(fractal_data, AM_FULL_ITERATIONS);
    render_ascii_graph(fractal_data, AM_PERIODS);
}

int console_app_handle_command(int argc, char *argv[]) {

    // Resolution for output image and ASCII graph
    resolution_t resolution;

    // Matrix with number of Mandelbrot formula iterations needed for each pixel to diverge.
    fractal_data_t fractal_data;

    // The tile we want to draw with complex points coordinates
    ztile_t tile;

    // Calculate the time taken for fractal matrix generation
    clock_t time;

    // App config
    config_t config;

    // Console command arguments
    struct arguments arguments;

    app_config_init(&config);

    // Parse arguments
    arguments.config = &config;
    arguments.resolution = &resolution;
    argp_parse(&argp, argc, argv, 0, 0, &arguments);

    // Define tile

    // TODO: ge tile pos/size from console arguments
    ztile_init(&tile);
    ztile_set_completed_mandelbrot_set(&tile, &config);

    // Calculate fractal data

    fractal_data_init(&fractal_data, resolution);
    // TODO: time -> output parameter
    time = clock();
    fractal_data_calculate_points(&fractal_data, tile, &config);
    time = clock() - time;

    ztile_clean(&tile);

    // Print extra metadata output

    if (app_config_verbose_option_enabled(&config, VO_PRINT_PERFORMANCE_DATA)) {
        print_performance_data(time, resolution, &config);
    }

    if (app_config_verbose_option_enabled(&config, VO_PRINT_FRACTAL_DATA)) {
        print_fractal_data(fractal_data);
    }

    // Write out output files

    if (arguments.generate_all_samples) {
        generate_all_samples(fractal_data);
    } else {
        switch(arguments.format) {
            case FORMAT_PPM:
                render_ppm_image(fractal_data, arguments.color_map);
                break;
            case FORMAT_ASCII_GRAPH:
                render_ascii_graph(fractal_data, arguments.ascii_map);
                break;
            default:
                printf("Exception. Invalid output format. Valid formats: PPM (0) or ASCII_GRAPH (1).\n");
                abort();
        }
    }

    fractal_data_clean(&fractal_data);

    return 0;
}
