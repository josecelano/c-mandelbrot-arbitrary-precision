#include <stdio.h>
#include <stdlib.h>
#include "mandelbrot/fractal.h"
#include "mandelbrot/image.h"
#include "mandelbrot/ascii_graph.h"
#include "mandelbrot/ztile.h"

/**
 * It renders a Mandelbrot fractal image in PPM format.
 * @param fractal_resolution resolution
 * @param iterations_taken_matrix
 */
void render_ppm_image(fractal_resolution resolution, int *iterations_taken_matrix) {
    char img_filename[50];

    sprintf(img_filename, "mandelbrot-%dx%d.ppm", resolution.width, resolution.height);

    render_and_write_out_image(img_filename, resolution, iterations_taken_matrix);
}

/**
 * It renders a txt file with a Mandelbrot ASCII graph.
 * @param fractal_resolution resolution
 * @param iterations_taken_matrix
 */
void render_ascii_graph(fractal_resolution resolution, int *iterations_taken_matrix) {
    char txt_filename[50];

    sprintf(txt_filename, "mandelbrot-%dx%d.txt", resolution.width, resolution.height);

    render_and_write_out_ascii_graph(txt_filename, resolution, iterations_taken_matrix);
}

int main(int argc, const char *argv[]) {

    // Bits of precision for C complex and real math operations library: http://arblib.org/acb.html#precision-and-comparisons
    slong prec = 32;

    // Resolution for output image and ASCII graph
    fractal_resolution resolution = {256, 256};

    // Max number of iterations for Mandelbrot formula
    int max_iterations = 100;

    // The tile we want to draw with complex points coordinates
    ztile tile;

    // Matrix[width][height] with number of Mandelbrot formula iterations needed for each pixel to diverge.
    // -1 for point/pixel inside Mandelbrot Set
    int *iterations_taken_matrix = malloc(resolution.width * resolution.height * sizeof *iterations_taken_matrix);

    ztile_init(&tile);
    ztile_set_completed_mandelbrot_set(&tile, prec);

    calculate_points(tile, resolution, max_iterations, prec, iterations_taken_matrix);

    ztile_clean(&tile);

    render_ppm_image(resolution, iterations_taken_matrix);

    render_ascii_graph(resolution, iterations_taken_matrix);

    free(iterations_taken_matrix);

    return 0;
}