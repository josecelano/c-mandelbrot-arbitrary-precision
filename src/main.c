#include <stdio.h>
#include <stdlib.h>

#include "mandelbrot/application/config.h"
#include "mandelbrot/domain/fractal.h"
#include "mandelbrot/domain/set.h"
#include "mandelbrot/domain/ztile.h"
#include "mandelbrot/infrastructure/ascii_graph_file.h"
#include "mandelbrot/infrastructure/ppm_image_file.h"
#include "mandelbrot/presentation/output.h"

// TODO: Hexagonal architecture refactor in progress.
//  * Move render_* functions to application/command and presentation/console-command folders.

/**
 * It renders a Mandelbrot fractal image in PPM format.
 */
void render_ppm_image(fractal_data_t fractal_data) {
    char img_filename[50];

    sprintf(img_filename, "./output/mandelbrot-%dx%d.ppm",
            fractal_data.resolution.width,
            fractal_data.resolution.height
    );

    render_and_write_out_image(img_filename, fractal_data);
}

/**
 * It renders a txt file with a Mandelbrot ASCII graph.
 */
void render_ascii_graph(fractal_data_t fractal_data) {
    char txt_filename[50];

    sprintf(txt_filename, "./output/mandelbrot-%dx%d.txt",
            fractal_data.resolution.width,
            fractal_data.resolution.height
    );

    render_and_write_out_ascii_graph(txt_filename, fractal_data);
}

/**
 * It renders a txt file with a Mandelbrot iterations matrix.
 */
void render_iterations_taken_matrix(fractal_data_t fractal_data) {
    char txt_filename[50];

    sprintf(txt_filename, "./output/mandelbrot-iter-%dx%d.txt",
            fractal_data.resolution.width,
            fractal_data.resolution.height
    );

    render_and_write_out_iterations_matrix(txt_filename, fractal_data);
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

    ztile_set_completed_mandelbrot_set(&tile, config);

    time = clock();
    fractal_data_calculate_points(&fractal_data, tile, config);
    time = clock() - time;

    ztile_clean(&tile);

    print_performance_data(time, resolution, config);

    print_fractal_matrix_data(fractal_data);

    render_ppm_image(fractal_data);

    render_ascii_graph(fractal_data);

    render_iterations_taken_matrix(fractal_data);

    fractal_data_clean(&fractal_data);

    return 0;
}