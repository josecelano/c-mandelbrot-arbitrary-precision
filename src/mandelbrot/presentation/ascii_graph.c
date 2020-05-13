#include <stdio.h>

#include "../domain/fractal.h"
#include "../domain/set.h"
#include "ascii_graph.h"

void set_point_character(
        char *pixel_char,
        int x, int y,
        int width, int height, int *iterations_taken_matrix
) {
    int num_iter_for_pixel;

    num_iter_for_pixel = get_iterations_taken_for_point(x, y, width, height, iterations_taken_matrix);

    if (num_iter_for_pixel == MAX_ITERATIONS) {
        // Inside Mandelbrot Set
        *pixel_char = '@';
    } else {
        // Outside Mandelbrot Set
        *pixel_char = ' ';
    }
}