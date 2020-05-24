#include <stdio.h>

#include "../domain/fractal.h"
#include "../domain/set.h"
#include "ascii_graph.h"

void set_point_character(char *point_char, point_t p, fractal_data_t fractal_data) {

    int ret = fractal_matrix_point_belongs_to_mandelbrot_set(p, fractal_data);

    if (ret == INSIDE) {
        // Inside Mandelbrot Set
        *point_char = '@';
        return;
    }

    // Outside Mandelbrot Set
    *point_char = ' ';
}