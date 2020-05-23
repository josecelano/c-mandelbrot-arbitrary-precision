#include <string.h>
#include <stdio.h>

#include "color.h"
#include "pixel.h"
#include "set.h"

void color_pixel_with_black_and_white_color_map(rgb_color color, pixel px, fractal_matrix iterations_taken_matrix) {
    const char black[3] = {0, 0, 0};
    const char white[3] = {255, 255, 255};
    int ret;
    point p;

    point_set_from_pixel(&p, px);

    ret = fractal_matrix_point_belongs_to_mandelbrot_set(p, iterations_taken_matrix);

    if (ret == INSIDE) {
        strncpy(color, black, RBG_COLOR_SIZE);
        return;
    }

    strncpy(color, white, RBG_COLOR_SIZE);
}