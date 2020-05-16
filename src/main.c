#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "mandelbrot/infrastructure/ascii_graph_file.h"
#include "mandelbrot/domain/fractal.h"
#include "mandelbrot/domain/set.h"
#include "mandelbrot/domain/ztile.h"
#include "mandelbrot/infrastructure/ppm_image_file.h"

// TODO: Hexagonal architecture refactor in progress.
//  * Move render_* functions to application/command and presentation/console-command folders.

/**
 * It renders a Mandelbrot fractal image in PPM format.
 */
void render_ppm_image(fractal_matrix iterations_taken_matrix) {
    char img_filename[50];

    sprintf(img_filename, "./output/mandelbrot-%dx%d.ppm",
            iterations_taken_matrix.resolution.width,
            iterations_taken_matrix.resolution.height
    );

    render_and_write_out_image(img_filename, iterations_taken_matrix);
}

/**
 * It renders a txt file with a Mandelbrot ASCII graph.
 */
void render_ascii_graph(fractal_matrix iterations_taken_matrix) {
    char txt_filename[50];

    sprintf(txt_filename, "./output/mandelbrot-%dx%d.txt",
            iterations_taken_matrix.resolution.width,
            iterations_taken_matrix.resolution.height
    );

    render_and_write_out_ascii_graph(txt_filename, iterations_taken_matrix);
}

/**
 * It renders a txt file with a Mandelbrot iterations matrix.
 */
void render_iterations_taken_matrix(fractal_matrix iterations_taken_matrix) {
    char txt_filename[50];

    sprintf(txt_filename, "./output/mandelbrot-iter-%dx%d.txt",
            iterations_taken_matrix.resolution.width,
            iterations_taken_matrix.resolution.height
    );

    render_and_write_out_iterations_matrix(txt_filename, iterations_taken_matrix);
}

void print_performance_data(
        clock_t time,
        fractal_resolution resolution,
        int max_iterations,
        slong prec
) {
    int number_of_pixels = resolution.width * resolution.height;
    double time_taken_in_seconds = ((double) time) / CLOCKS_PER_SEC;
    long double time_taken_in_nanoseconds = time_taken_in_seconds * 1000000000;

    printf("\nFor %dx%dpx image:\n", resolution.width, resolution.height);
    printf("* Size: %dx%dpx (%d)\n", resolution.width, resolution.height, number_of_pixels);
    printf("* Max iter: %d\n", max_iterations);
    printf("* Precision: %ld\n", prec);
    printf("* Time for matrix generation: %fs = %Lfns\n", time_taken_in_seconds, time_taken_in_nanoseconds);
    printf("* Performance: %Le‬ ns/px\n",
           ((long double) time_taken_in_seconds / number_of_pixels) * 1000000000); // In nanoseconds
    printf("* Minimum complex x increment: %Le (4/%d)\n", (long double) 4 / resolution.width, resolution.width);
    printf("* Minimum complex y increment: %Le (4/%d)\n", (long double) 4 / resolution.height, resolution.height);
}

int main(int argc, const char *argv[]) {

    // Bits of precision for C complex and real math operations library
    // http://arblib.org/acb.html#precision-and-comparisons
    slong prec = 32;

    // Max number of iterations for Mandelbrot formula
    int max_iterations = 100;

    // Resolution for output image and ASCII graph
    fractal_resolution resolution = {256, 256};

    // Matrix with number of Mandelbrot formula iterations needed for each pixel to diverge.
    fractal_matrix iterations_taken_matrix;

    // The tile we want to draw with complex points coordinates
    ztile tile;

    // Calculate the time taken for fractal matrix generation
    clock_t time;

    // Print progress
    int print_progress = 1;

    fractal_matrix_init(&iterations_taken_matrix, resolution);

    ztile_init(&tile);

    ztile_set_completed_mandelbrot_set(&tile, prec);

    time = clock();
    fractal_matrix_calculate_points(tile, max_iterations, prec, print_progress, &iterations_taken_matrix);
    time = clock() - time;

    ztile_clean(&tile);

    print_performance_data(time, resolution, max_iterations, prec);

    render_ppm_image(iterations_taken_matrix);

    render_ascii_graph(iterations_taken_matrix);

    render_iterations_taken_matrix(iterations_taken_matrix);

    fractal_matrix_clean(&iterations_taken_matrix);

    return 0;
}