#include <stdio.h>

#include "../domain/set.h"
#include "../presentation/ascii_graph.h"
#include "ascii_graph_file.h"

void render_and_write_out_ascii_graph(char *filename, fractal_matrix iterations_taken_matrix) {
    int x, y, num_iter_for_pixel;
    char point_char[1];
    FILE *fp;
    fractal_resolution resolution = iterations_taken_matrix.resolution;

    fp = fopen(filename, "w");

    for (y = 0; y < resolution.height; y++) {
        for (x = 0; x < resolution.width; x++) {

            point p = {x, y};

            set_point_character(
                    point_char, p,
                    iterations_taken_matrix);

            fwrite(point_char, 1, 1, fp);
        }

        fwrite("\n", sizeof(char), 1, fp);
    }

    fclose(fp);
}

void render_and_write_out_iterations_matrix(char *filename, fractal_matrix iterations_taken_matrix) {
    int x, y, num_iter_for_pixel, ret;
    char num_iter_str[50];
    FILE *fp;
    fractal_resolution resolution = iterations_taken_matrix.resolution;
    point p;

    fp = fopen(filename, "w");

    for (y = 0; y < resolution.height; y++) {
        for (x = 0; x < resolution.width; x++) {

            point_set(&p, x, y);

            num_iter_for_pixel = fractal_matrix_get_num_iter_per_point(p, iterations_taken_matrix);

            ret = fractal_matrix_point_belongs_to_mandelbrot_set(p, iterations_taken_matrix);

            // TODO: 3 literal (and 3 spaces) is the number of digits for the greatest number of iterations during
            // matrix calculations which is a constant in main.c right now but it has to be calculated dynamically.
            // We should add function for fractal_matrix that returns max number of interactions in the matrix data,
            // and calculate the number of digits of that value. The function can store the maximum while is calculating
            // the points.
            if (ret == INSIDE) {
                // Inside Mandelbrot Set
                fwrite("   ", 1, 3, fp);
            } else {
                // Outside Mandelbrot Set
                sprintf(num_iter_str, "%3d", num_iter_for_pixel);
                fwrite(num_iter_str, 1, 3, fp);
            }
        }
        fwrite("\n", sizeof(char), 1, fp);
    }

    fclose(fp);
}

