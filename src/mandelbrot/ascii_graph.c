#include <stdio.h>
#include "ascii_graph.h"
#include "set.h"

void render_and_write_out_ascii_graph(char *filename, fractal_resolution resolution, int *iterations_taken_matrix) {
    int x, y, num_iter_for_pixel;
    FILE *fp;

    fp = fopen(filename, "w");

    for (y = 0; y < resolution.height; y++) {
        for (x = 0; x < resolution.width; x++) {

            num_iter_for_pixel = get_iterations_taken_for_point(
                    x, y,
                    resolution.width, resolution.height, iterations_taken_matrix
            );

            if (num_iter_for_pixel == MAX_ITERATIONS) {
                // Inside Mandelbrot Set
                fwrite("@", 1, 1, fp);
            } else {
                // Outside Mandelbrot Set
                fwrite(" ", 1, 1, fp);
            }
        }

        fwrite("\n", sizeof(char), 1, fp);
    }

    fclose(fp);
}

/**
 * @param filename
 * @param resolution
 * @param iterations_taken_matrix
 */
void
render_and_write_out_iterations_matrix(char *filename, fractal_resolution resolution, int *iterations_taken_matrix) {
    int x, y, num_iter_for_pixel;
    char num_iter_str[50];
    FILE *fp;

    fp = fopen(filename, "w");

    for (y = 0; y < resolution.height; y++) {
        for (x = 0; x < resolution.width; x++) {

            num_iter_for_pixel = iterations_taken_matrix[(y * resolution.width) + x];

            // TODO: 3 literal (and 3 spaces) is the number of digits for MAX_ITERATIONS number.
            if (num_iter_for_pixel == MAX_ITERATIONS) {
                // Inside Mandelbrot Set
                fwrite("   ", 1, 3, fp);
            } else {
                // Outside Mandelbrot Set
                sprintf(num_iter_str, "%3d", iterations_taken_matrix[(y * resolution.width) + x]);
                fwrite(num_iter_str, 1, 3, fp);
            }
        }
        fwrite("\n", sizeof(char), 1, fp);
    }

    fclose(fp);
}

