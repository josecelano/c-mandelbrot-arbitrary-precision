#include <stdio.h>

#include "../domain/fractal.h"
#include "../domain/set.h"
#include "ascii_graph.h"

void set_point_character(char *point_char, point_t point, fractal_data_t fractal_data) {

    calculated_point_t calculated_point;

    //int ret = fractal_matrix_point_belongs_to_mandelbrot_set(p, fractal_data);
    fractal_matrix_get_calculated_point(fractal_data, point, &calculated_point);

    if (calculated_point.is_inside) {
        // Inside Mandelbrot Set
        *point_char = '@';
        return;
    }

    // Outside Mandelbrot Set
    *point_char = ' ';
}