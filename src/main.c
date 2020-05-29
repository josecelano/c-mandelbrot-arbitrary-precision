#include <stdio.h>
#include <stdlib.h>

#include "mandelbrot/application/config.h"
#include "mandelbrot/domain/fractal.h"
#include "mandelbrot/domain/set.h"
#include "mandelbrot/domain/ztile.h"
#include "mandelbrot/infrastructure/ascii_graph_file.h"
#include "mandelbrot/infrastructure/ppm_image_file.h"
#include "mandelbrot/presentation/output.h"
#include "mandelbrot/domain/ascii_graph/ascii_map.h"
#include "mandelbrot/domain/ascii_graph/ascii_graph.h"
#include "mandelbrot/domain/image/color_map.h"

// TODO: Hexagonal architecture refactor in progress.
//  * Move render_* functions to application/command and presentation/console-command folders.

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

int main(int argc, const char *argv[]) {

    // Resolution for output image and ASCII graph
    resolution_t resolution = {256, 256};

    // Matrix with number of Mandelbrot formula iterations needed for each pixel to diverge.
    fractal_data_t fractal_data;

    // The tile we want to draw with complex points coordinates
    ztile_t tile;

    // Calculate the time taken for fractal matrix generation
    clock_t time;

    config_t config;

    app_config_init(&config);

    fractal_data_init(&fractal_data, resolution);

    ztile_init(&tile);

    ztile_set_completed_mandelbrot_set(&tile, &config);

    // Disable optimisation options (enabled by default)
    app_config_disable_optimisation_option(&config, OO_MAIN_CARDIOID_DETECTION);
    app_config_disable_optimisation_option(&config, OO_PERIOD2_DETECTION);
    app_config_disable_optimisation_option(&config, OO_PERIODICITY_CHECKING);

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