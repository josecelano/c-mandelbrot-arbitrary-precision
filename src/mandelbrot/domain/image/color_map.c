#include <string.h>
#include <stdio.h>
#include "color.h"
#include "pixel.h"
#include "../set.h"
#include "color_map.h"

void color_pixel_with_black_on_white_color_map(pixel *px, fractal_data_t fractal_data) {
    rgb_color black = {0, 0, 0};
    rgb_color white = {255, 255, 255};

    int ret;
    point_t p;

    point_set_from_pixel(&p, *px);

    ret = fractal_matrix_point_belongs_to_mandelbrot_set(p, fractal_data);

    if (ret == INSIDE) {
        pixel_set_color(px, black);
        return;
    }

    pixel_set_color(px, white);
}

void color_pixel_with_white_on_black_color_map(pixel *px, fractal_data_t fractal_data) {
    rgb_color black = {0, 0, 0};
    rgb_color white = {255, 255, 255};

    int ret;
    point_t p;

    point_set_from_pixel(&p, *px);

    ret = fractal_matrix_point_belongs_to_mandelbrot_set(p, fractal_data);

    if (ret == INSIDE) {
        pixel_set_color(px, white);
        return;
    }

    pixel_set_color(px, black);
}