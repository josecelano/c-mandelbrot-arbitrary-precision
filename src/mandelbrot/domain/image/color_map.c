#include <string.h>
#include <stdio.h>

#include "../calculated_point.h"
#include "../set.h"
#include "./color.h"
#include "./color_map.h"
#include "./pixel.h"

void color_pixel_with_black_on_white_color_map(pixel *px, fractal_data_t fractal_data) {
    rgb_color black = {0, 0, 0};
    rgb_color white = {255, 255, 255};

    point_t point;
    calculated_point_t calculated_point;

    point_copy_coordinates_from_pixel(&point, *px);

    fractal_data_get_calculated_point(fractal_data, point, &calculated_point);

    if (calculated_point.is_inside) {
        pixel_set_color(px, black);
        return;
    }

    pixel_set_color(px, white);
}

void color_pixel_with_white_on_black_color_map(pixel *px, fractal_data_t fractal_data) {
    rgb_color black = {0, 0, 0};
    rgb_color white = {255, 255, 255};

    point_t point;
    calculated_point_t calculated_point;

    point_copy_coordinates_from_pixel(&point, *px);

    fractal_data_get_calculated_point(fractal_data, point, &calculated_point);

    if (calculated_point.is_inside) {
        pixel_set_color(px, white);
        return;
    }

    pixel_set_color(px, black);
}