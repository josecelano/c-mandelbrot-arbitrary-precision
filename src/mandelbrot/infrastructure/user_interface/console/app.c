#include <argp.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../../application/config.h"
#include "../../../domain/fractal.h"
#include "./app.h"
#include "./commands/render_all_samples_command.h"
#include "./commands/render_ascii_graph_command.h"
#include "./commands/render_ppm_image_command.h"

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

void arguments_init(struct arguments *arguments, config_t *config, resolution_t *resolution) {
    arguments->render_all_samples = 0;
    arguments->config = config;
    arguments->resolution = resolution;
}

int handle_command(struct arguments *arguments, config_t *config, resolution_t resolution) {
    if (arguments->render_all_samples) {
        return render_all_samples_command(config, resolution);
    } else {
        switch (arguments->format) {
            case FORMAT_PPM:
                return render_ppm_image_command(
                        config,
                        resolution,
                        arguments->left_bottom_zx, arguments->left_bottom_zy,
                        arguments->top_right_zx, arguments->top_right_zy,
                        arguments->color_map
                );
                break;
            case FORMAT_ASCII_GRAPH:
                return render_ascii_graph_command(
                        config,
                        resolution,
                        arguments->left_bottom_zx, arguments->left_bottom_zy,
                        arguments->top_right_zx, arguments->top_right_zy,
                        arguments->ascii_map
                );
                break;
            default:
                printf("Exception. Invalid output format. Valid formats: PPM (0) or ASCII_GRAPH (1).\n");
                abort();
        }
    }
}

int console_app_run(int argc, char **argv) {

    config_t config;                        // App config.
    resolution_t resolution = {256, 256};   // Resolution for output image and ASCII graph. Default 256x256.
    struct arguments arguments;             // Console command arguments.

    app_config_init(&config);
    arguments_init(&arguments, &config, &resolution);

    // Parse arguments
    argp_parse(&argp, argc, argv, 0, 0, &arguments);

    return handle_command(&arguments, &config, resolution);
}
