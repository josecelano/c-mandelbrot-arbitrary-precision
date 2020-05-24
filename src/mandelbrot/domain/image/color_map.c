#include <string.h>
#include <stdio.h>
#include "color.h"
#include "pixel.h"
#include "../set.h"
#include "color_map.h"

void color_pixel_with_black_and_white_color_map(pixel *px, fractal_matrix iterations_taken_matrix) {
    rgb_color rgb_black = {0, 0, 0};
    rgb_color rgb_white = {255, 255, 255};

    int ret;
    point p;

    point_set_from_pixel(&p, *px);

    ret = fractal_matrix_point_belongs_to_mandelbrot_set(p, iterations_taken_matrix);

    if (ret == INSIDE) {
        pixel_set_color(px, rgb_black);
        return;
    }

    pixel_set_color(px, rgb_white);
}