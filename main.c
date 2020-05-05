#include <stdio.h>
#include <stdlib.h>
#include "src/fractal.h"
#include "src/image.h"
#include "src/ascii_graph.h"

/**
 * It renders a Mandelbrot fractal image in PPM format.
 * @param res_x
 * @param res_y
 * @param iterations_taken_matrix
 */
void render_ppm_image(int res_x, int res_y, int *iterations_taken_matrix) {
    char img_filename[50];

    sprintf(img_filename, "mandelbrot-%dx%d.ppm", res_x, res_y);

    render_and_write_out_image(img_filename, res_x, res_y, iterations_taken_matrix);
}

/**
 * It renders a txt file with a Mandelbrot ASCII graph.
 * @param columns
 * @param rows
 * @param iterations_taken_matrix
 */
void render_ascii_graph(int columns, int rows, int *iterations_taken_matrix) {
    char txt_filename[50];

    sprintf(txt_filename, "mandelbrot-%dx%d.txt", columns, rows);

    render_and_write_out_ascii_graph(txt_filename, columns, rows, iterations_taken_matrix);
}

int main(int argc, const char *argv[]) {

    // Bits of precision for C complex and real math operations library: http://arblib.org/acb.html#precision-and-comparisons
    slong prec = 32;

    // Resolution for output image and ASCII graph
    int res_x = 256, res_y = 256;

    // Max number of iterations for Mandelbrot formula
    int max_iterations = 200;

    // Matrix[res_x][res_y] with number of Mandelbrot formula iterations needed for each pixel to diverge.
    // -1 for point/pixel inside Mandelbrot Set
    int *iterations_taken_matrix = malloc(res_x * res_y * sizeof *iterations_taken_matrix);

    calculate_points(res_x, res_y, max_iterations, prec, iterations_taken_matrix);

    render_ppm_image(res_x, res_y, iterations_taken_matrix);

    render_ascii_graph(res_x, res_y, iterations_taken_matrix);

    free(iterations_taken_matrix);

    return 0;
}