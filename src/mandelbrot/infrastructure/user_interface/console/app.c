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
 * Sample commands:
 *
 * IMAGE: full mandelbrot 256x256px black on white color map
 * ./mandelbrot -p -- -2.0 -2.0 2.0 2.0 256 256 0 0
 *
 * ASCII GRAPH: full mandelbrot 256x256char @ ascii map
 * ./mandelbrot -p -- -2.0 -2.0 2.0 2.0 256 256 0 0
 */

const char *argp_program_version = "mandelbrot 1.0.0";
const char *argp_program_bug_address = "https://github.com/josecelano/c-mandelbrot-arbitrary-precision/issues";
static char doc[] = "\nMandelbrot Set image and ASCII graph generator.\n" \
    "\n" \
    "ARGUMENTS:\n\n" \
    "[LEFT_BOTTOM_ZX]:   Left bottom tile x coordinate. For example -2.0\n" \
    "[LEFT_BOTTOM_ZY]:   Left bottom tile y coordinate. For example -2.0\n" \
    "[TOP_RIGHT_ZX]:     Right top tile x coordinate\n" \
    "[TOP_RIGHT_ZY]:     Right top tile y coordinate\n" \
    "[RES_X]:            Fractal resolution width\n" \
    "[RES_Y]:            Fractal resolution height\n" \
    "[FORMAT]:           PPM image = 0, ASCII graph = 1\n" \
    "[COLOR_MAP]:\n" \
    "   CM_BLACK_ON_WHITE = 0\n" \
    "   CM_WHITE_ON_BLACK = 1\n" \
    "   CM_COLORED_PERIODS = 2\n" \
    "[ASCII_MAP]:\n" \
    "   AM_AT_SIGN = 0\n" \
    "   AM_ITERATIONS = 1\n" \
    "   AM_FULL_ITERATIONS = 2\n" \
    "   AM_PERIODS = 2\n" \
    "\nOPTIONS:";
static char args_doc[] = "[LEFT_BOTTOM_ZX]... [LEFT_BOTTOM_ZY]... [TOP_RIGHT_ZX]... [TOP_RIGHT_ZY]... [RES_X]... [RES_Y]... [FORMAT]... [COLOR_MAP|ASCII_MAP]...";
static struct argp_option options[] = {
        // Verbose options
        {"vo_progress",         'p', 0, 0, "Verbose opt: Print progress"},
        {"vo_periods",          'e', 0, 0, "Verbose opt: Print periods"},
        {"vo_iterations",       't', 0, 0, "Verbose opt: Print iterations"},
        {"vo_performance_data", 'r', 0, 0, "Verbose opt: Print performance data"},
        {"vo_fractal_data",     'f', 0, 0, "Verbose opt: Print fractal data"},
        // Optimisation options
        {"op_main_cardioid",    'c', 0, 0, "Optimisation opt: Main cardioid detection"},
        {"op_period2",          'o', 0, 0, "Optimisation opt: Period 2 detection"},
        {"op_periodicity",      'y', 0, 0, "Optimisation opt: Periodicity checking"},
        // Dev extras
        {"render_all_samples",  'A', 0, 0, "Generate samples with all color/ascii maps"},
        {0}
};

struct arguments {
    // Options
    config_t *config;
    int render_all_samples;
    // Arguments
    char *left_bottom_zx;
    char *left_bottom_zy;
    char *top_right_zx;
    char *top_right_zy;
    resolution_t *resolution;
    enum {
        FORMAT_PPM = 0,
        FORMAT_ASCII_GRAPH = 1
    } format;
    color_map_t color_map;
    ascii_map_t ascii_map;
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
            app_config_enable_optimisation_option(arguments->config, OO_MAIN_CARDIOID_DETECTION);
            break;
        case 'o':
            app_config_enable_optimisation_option(arguments->config, OO_PERIOD2_DETECTION);
            break;
        case 'y':
            app_config_enable_optimisation_option(arguments->config, OO_PERIODICITY_CHECKING);
            break;

        case 'A':
            arguments->render_all_samples = 1;
            break;

        case ARGP_KEY_ARG:
            if (arguments->render_all_samples == 1) {
                // Arguments not needed for samples generation
                break;
            }
            switch (state->arg_num) {
                case 0: // LEFT_BOTTOM_ZX
                    arguments->left_bottom_zx = arg;
                    break;
                case 1: // LEFT_BOTTOM_ZY
                    arguments->left_bottom_zy = arg;
                    break;
                case 2: // TOP_RIGHT_ZX
                    arguments->top_right_zx = arg;
                    break;
                case 3: // TOP_RIGHT_ZY
                    arguments->top_right_zy = arg;
                    break;
                case 4: // RES_X
                    arguments->resolution->width = atoi(arg);
                    break;
                case 5: // RES_Y
                    arguments->resolution->height = atoi(arg);
                    break;
                case 6: // FORMAT
                    arguments->format = atoi(arg);
                    break;
                case 7: // COLOR_MAP | ASCII_MAP
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

void render_all_samples(fractal_data_t fractal_data) {
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

void fractal_data_calculate(fractal_data_t *fractal_data, ztile_t tile, config_t *config, clock_t *execution_time) {
    *execution_time = clock();
    fractal_data_calculate_points(fractal_data, tile, config);
    *execution_time = clock() - *execution_time;
}

int console_app_handle_command(int argc, char *argv[]) {

    config_t config;                        // App config.
    ztile_t tile;                           // The tile we want to draw with complex points coordinates.
    resolution_t resolution = {256, 256};   // Resolution for output image and ASCII graph. Default 256x256.
    fractal_data_t fractal_data;            // Matrix with calculated points.
    clock_t fractal_data_generation_time;   // Calculate the time taken for fractal data generation.
    struct arguments arguments;             // Console command arguments.

    app_config_init(&config);

    /* Parse arguments */

    arguments.config = &config;
    arguments.resolution = &resolution;
    argp_parse(&argp, argc, argv, 0, 0, &arguments);

    /* Set the tile */

    ztile_init(&tile);

    if (arguments.render_all_samples) {
        ztile_set_completed_mandelbrot_set(&tile, &config);
    } else {
        ztile_set_from_str(
                &tile,
                arguments.left_bottom_zx, arguments.left_bottom_zy,
                arguments.top_right_zx, arguments.top_right_zy,
                config.precision
        );
    }

    /* Calculate fractal data */

    fractal_data_init(&fractal_data, resolution);

    if (arguments.render_all_samples) {
        app_config_enable_optimisation_option(&config, OO_MAIN_CARDIOID_DETECTION);
        app_config_enable_optimisation_option(&config, OO_PERIOD2_DETECTION);
        app_config_enable_optimisation_option(&config, OO_PERIODICITY_CHECKING);
    }

    fractal_data_calculate(&fractal_data, tile, &config, &fractal_data_generation_time);

    /* Print extra metadata */

    if (app_config_verbose_option_enabled(&config, VO_PRINT_PERFORMANCE_DATA)) {
        print_performance_data(fractal_data_generation_time, resolution, &config);
    }

    if (app_config_verbose_option_enabled(&config, VO_PRINT_FRACTAL_DATA)) {
        print_fractal_data(fractal_data);
    }

    /* Write out output files */

    if (arguments.render_all_samples) {
        render_all_samples(fractal_data);
    } else {
        switch (arguments.format) {
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

    /* Clean data */

    ztile_clean(&tile);
    fractal_data_clean(&fractal_data);

    return 0;
}
