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
 * mandelbrot [OUTPUT_FORMAT] [Z_CENTER_X] [Z_CENTER_Y] [Z_WIDTH] [Z_HEIGHT] [RES_X] [RES_Y] [COLOR_MAP|ASCII_MAP] [FILENAME]
 *
 * IMAGE:
 * mandelbrot -i -2 -2 4 4 256 256 cm_black_on_white ./output/mandelbrot-black-on-white-256x256.ppm
 *
 * ASCII GRAPH:
 * mandelbrot -a -2 -2 4 4 256 256 am_at_sign ./output/mandelbrot-at-sign-256x256.txt
 */

const char *argp_program_version = "mandelbrot 1.0.0";
const char *argp_program_bug_address = "<josecelano@gmail.com>";
static char doc[] = "Mandelbrot Set image and ASCII graph generator.";
static char args_doc[] = "[RES_X]... [RES_Y]...";
static struct argp_option options[] = {
        // Output format
        {"image",                   'i', 0, 0, "Output format: Image PPM"},
        {"ascii_graph",             'a', 0, 0, "Output format: ASCII graph"},
        // Verbose options
        {"print_progress",          'p', 0, 0, "Verbose option: Print progress"},
        {"print_periods",           'e', 0, 0, "Verbose option: Print periods"},
        {"print_iterations",        't', 0, 0, "Verbose option: Print iterations"},
        {"print_performance_data",  'r', 0, 0, "Verbose option: Print performance data"},
        {"print_fractal_data",      'f', 0, 0, "Verbose option: Print fractal data"},
        // Optimisation options
        {"main_cardioid_detection", 'c', 0, 0, "Optimisation option: Main cardioid detection"},
        {"period2_detection",       'o', 0, 0, "Optimisation option: Period 2 detection"},
        {"periodicity_checking",    'y', 0, 0, "Optimisation option: Periodicity checking"},
        {0}
};

struct arguments {
    enum {
        OF_IMAGE,
        OF_ASCII_GRAPH
    } output_format;
    config_t *config;
    resolution_t *resolution;
};

static error_t parse_opt(int key, char *arg, struct argp_state *state) {
    struct arguments *arguments = state->input;
    switch (key) {
        case 'i':
            arguments->output_format = OF_IMAGE;
            break;
        case 'a':
            arguments->output_format = OF_ASCII_GRAPH;
            break;

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

        case ARGP_KEY_ARG:
            switch (state->arg_num) {
                case 0: // RES_X
                    arguments->resolution->width = atoi(arg);
                    break;
                case 1: // RES_Y
                    arguments->resolution->height = atoi(arg);
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

    switch (color_map) {
        case CM_BLACK_ON_WHITE:
            strcpy(color_map_name, "black-on-white");
            break;
        case CM_WHITE_ON_BLACK:
            strcpy(color_map_name, "white-on-black");
            break;
        case CM_COLORED_PERIODS:
            strcpy(color_map_name, "colored-periods");
            break;
    }

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

    switch (ascii_map) {
        case AM_AT_SIGN:
            strcpy(ascii_map_name, "at-sign");
            break;
        case AM_ITERATIONS:
            strcpy(ascii_map_name, "iterations");
            break;
        case AM_FULL_ITERATIONS:
            strcpy(ascii_map_name, "full-iterations");
            break;
        case AM_PERIODS:
            strcpy(ascii_map_name, "periods");
            break;
    }

    sprintf(img_filename, "./output/mandelbrot-%s-%dx%d.txt",
            ascii_map_name,
            fractal_data.resolution.width,
            fractal_data.resolution.height
    );

    render_fractal_and_write_out_the_text_file(img_filename, fractal_data, ascii_map);
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

    config_t config;

    struct arguments arguments;


    app_config_init(&config);

    arguments.config = &config;
    arguments.resolution = &resolution;

    // Parse arguments
    argp_parse(&argp, argc, argv, 0, 0, &arguments);

    fractal_data_init(&fractal_data, resolution);

    ztile_init(&tile);
    ztile_set_completed_mandelbrot_set(&tile, &config);

    time = clock();
    fractal_data_calculate_points(&fractal_data, tile, &config);
    time = clock() - time;

    ztile_clean(&tile);

    if (app_config_verbose_option_enabled(&config, VO_PRINT_PERFORMANCE_DATA)) {
        print_performance_data(time, resolution, &config);
    }
    if (app_config_verbose_option_enabled(&config, VO_PRINT_FRACTAL_DATA)) {
        print_fractal_data(fractal_data);
    }

    // Render images
    render_ppm_image(fractal_data, CM_BLACK_ON_WHITE);
    render_ppm_image(fractal_data, CM_WHITE_ON_BLACK);
    render_ppm_image(fractal_data, CM_COLORED_PERIODS);

    // Render ascii graphs
    render_ascii_graph(fractal_data, AM_AT_SIGN);
    render_ascii_graph(fractal_data, AM_ITERATIONS);
    render_ascii_graph(fractal_data, AM_FULL_ITERATIONS);
    render_ascii_graph(fractal_data, AM_PERIODS);

    fractal_data_clean(&fractal_data);

    return 0;
}
