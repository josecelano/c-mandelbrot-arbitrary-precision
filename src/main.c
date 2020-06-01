#include <stdio.h>
#include <stdlib.h>
#include <argp.h>
#include <stdbool.h>

#include "mandelbrot/application/config.h"
#include "mandelbrot/domain/fractal.h"
#include "mandelbrot/domain/set.h"
#include "mandelbrot/domain/ztile.h"
#include "mandelbrot/infrastructure/user_interface/files/ascii_graph_file.h"
#include "mandelbrot/infrastructure/user_interface/files/ppm_image_file.h"
#include "mandelbrot/presentation/output.h"
#include "mandelbrot/domain/ascii_graph/ascii_map.h"
#include "mandelbrot/domain/ascii_graph/ascii_graph.h"
#include "mandelbrot/domain/image/color_map.h"

/*
 * TODO: WIP. Only verbose options are obtained from console arguments.
 *
 * CONSOLE COMMAND:
 * mandelbrot [OUTPUT_FORMAT] [CENTER_X] [CENTER_Y] [WIDTH] [HEIGHT] [RES_X] [RES_Y] [COLOR_MAP|ASCII_MAP] [FILENAME]
 *
 * IMAGE:
 * mandelbrot -i -2 -2 4 4 256 256 cm_black_on_white ./output/mandelbrot-256x256.ppm
 *
 * ASCII GRAPH:
 * mandelbrot -a -2 -2 4 4 256 256 am_at_sign ./output/mandelbrot-256x256.txt
 */

const char *argp_program_version = "mandelbrot 1.0.0";
const char *argp_program_bug_address = "<josecelano@gmail.com>";
static char doc[] = "Mandelbrot Set image and ASCII graph generator.";
static char args_doc[] = "[FILENAME]...";
static struct argp_option options[] = {
        // Output format
        {"image",            'i', 0, 0, "Image PPM"},
        {"ascii_graph",      'a', 0, 0, "ASCII graph"},
        // Verbose options
        {"print_progress",   'p', 0, 0, "Print progress"},
        {"print_periods",    'e', 0, 0, "Print periods"},
        {"print_iterations", 't', 0, 0, "Print iterations"},
        // Optimisation options
        {0}
};

struct arguments {
    enum {
        OF_IMAGE,
        OF_ASCII_GRAPH
    } output_format;
    config_t *config;
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

        case ARGP_KEY_ARG:
            return 0;
        default:
            return ARGP_ERR_UNKNOWN;
    }
    return 0;
}

static struct argp argp = {options, parse_opt, args_doc, doc, 0, 0, 0};

/**
 * It renders a Mandelbrot fractal image in PPM format.
 * Inside -> black
 * Outside -> white
 */
void render_ppm_image_with_back_on_white_color_map(fractal_data_t fractal_data) {
    char img_filename[50];

    sprintf(img_filename, "./output/mandelbrot-%dx%d.ppm",
            fractal_data.resolution.width,
            fractal_data.resolution.height
    );

    render_and_write_out_image(img_filename, fractal_data, CM_BLACK_ON_WHITE);
}

/**
 * It renders a Mandelbrot fractal image in PPM format.
 * Inside -> white
 * Outside -> black
 */
void render_ppm_image_with_white_on_black_color_map(fractal_data_t fractal_data) {
    char img_filename[50];

    sprintf(img_filename, "./output/mandelbrot-white-on-black-%dx%d.ppm",
            fractal_data.resolution.width,
            fractal_data.resolution.height
    );

    render_and_write_out_image(img_filename, fractal_data, CM_WHITE_ON_BLACK);
}

/**
 * It renders a Mandelbrot image where each point inside have a different color depending on the period.
 */
void render_ppm_image_with_colored_periods_color_map(fractal_data_t fractal_data) {
    char img_filename[50];

    sprintf(img_filename, "./output/mandelbrot-periods-%dx%d.ppm",
            fractal_data.resolution.width,
            fractal_data.resolution.height
    );

    render_and_write_out_image(img_filename, fractal_data, CM_COLORED_PERIODS);
}

/**
 * It renders a txt file with a Mandelbrot ASCII graph.
 */
void render_ascii_graph_with_at_sign_ascii_map(fractal_data_t fractal_data) {
    char txt_filename[50];

    sprintf(txt_filename, "./output/mandelbrot-%dx%d.txt",
            fractal_data.resolution.width,
            fractal_data.resolution.height
    );

    render_fractal_and_write_out_the_text_file(txt_filename, fractal_data, AM_AT_SIGN);
}

/**
 * It renders a txt file with the Mandelbrot iterations taken for points outside.
 */
void render_ascii_graph_with_iterations_ascii_map(fractal_data_t fractal_data) {
    char txt_filename[50];

    sprintf(txt_filename, "./output/mandelbrot-iter-%dx%d.txt",
            fractal_data.resolution.width,
            fractal_data.resolution.height
    );

    render_fractal_and_write_out_the_text_file(txt_filename, fractal_data, AM_ITERATIONS);
}

/**
 * It renders a txt file with the Mandelbrot iterations taken for all points outside (inside/outside).
 */
void render_ascii_graph_with_full_iterations_ascii_map(fractal_data_t fractal_data) {
    char txt_filename[50];

    sprintf(txt_filename, "./output/mandelbrot-full-iter-%dx%d.txt",
            fractal_data.resolution.width,
            fractal_data.resolution.height
    );

    render_fractal_and_write_out_the_text_file(txt_filename, fractal_data, AM_FULL_ITERATIONS);
}

/**
 * It renders a txt file with the found periods (for points inside Mandelbrot Set)
 * when period checking optimisation is used.
 */
void render_ascii_graph_with_periods_ascii_map(fractal_data_t fractal_data) {
    char txt_filename[50];

    sprintf(txt_filename, "./output/mandelbrot-periods-%dx%d.txt",
            fractal_data.resolution.width,
            fractal_data.resolution.height
    );

    render_fractal_and_write_out_the_text_file(txt_filename, fractal_data, AM_PERIODS);
}

int main(int argc, char *argv[]) {

    // Resolution for output image and ASCII graph
    resolution_t resolution = {256, 256};

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

    argp_parse(&argp, argc, argv, 0, 0, &arguments);

    fractal_data_init(&fractal_data, resolution);

    ztile_init(&tile);

    ztile_set_completed_mandelbrot_set(&tile, &config);

    time = clock();
    fractal_data_calculate_points(&fractal_data, tile, &config);
    time = clock() - time;

    ztile_clean(&tile);

    print_performance_data(time, resolution, &config);

    print_fractal_matrix_data(fractal_data);

    // Render images

    render_ppm_image_with_back_on_white_color_map(fractal_data);

    render_ppm_image_with_white_on_black_color_map(fractal_data);

    render_ppm_image_with_colored_periods_color_map(fractal_data);

    // Render ascii graphs

    render_ascii_graph_with_at_sign_ascii_map(fractal_data);

    render_ascii_graph_with_iterations_ascii_map(fractal_data);

    render_ascii_graph_with_full_iterations_ascii_map(fractal_data);

    render_ascii_graph_with_periods_ascii_map(fractal_data);


    fractal_data_clean(&fractal_data);

    return 0;
}