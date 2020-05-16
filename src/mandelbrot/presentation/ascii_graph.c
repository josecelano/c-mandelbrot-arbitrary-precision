#include <stdio.h>

#include "../domain/fractal.h"
#include "../domain/set.h"
#include "ascii_graph.h"

void set_point_character(char *pixel_char, int x, int y, fractal_matrix iterations_taken_matrix) {
    int num_iter_for_pixel;

    num_iter_for_pixel = fractal_matrix_get_num_iter_per_point(x, y, iterations_taken_matrix);

    if (num_iter_for_pixel == MAX_ITERATIONS) {
        // Inside Mandelbrot Set
        *pixel_char = '@';
    } else {
        // Outside Mandelbrot Set
        *pixel_char = ' ';
    }
}