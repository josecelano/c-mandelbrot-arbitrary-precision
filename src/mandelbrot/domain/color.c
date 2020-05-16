#include <string.h>
#include <stdio.h>

#include "color.h"
#include "set.h"

void color_pixel_with_black_and_white_color_map(rgb_color color, int x, int y, fractal_matrix iterations_taken_matrix) {
    const char black[3] = {0, 0, 0};
    const char white[3] = {255, 255, 255};
    int ret;

    ret = fractal_matrix_point_belongs_to_mandelbrot_set(x, y, iterations_taken_matrix);

    if (ret == INSIDE) {
        strncpy(color, black, RBG_COLOR_SIZE);
        return;
    }

    strncpy(color, white, RBG_COLOR_SIZE);
}