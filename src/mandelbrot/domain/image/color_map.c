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

void color_pixel_with_periods_color_map(pixel *px, fractal_data_t fractal_data) {
    point_t point;
    calculated_point_t calculated_point;

    rgb_color white = {255, 255, 255};
    rgb_color black = {0, 0, 0};
    rgb_color period_color_map[8] = {
            {60,  63,  104},  // Period 1
            {37,  62,  141},
            {0,   127, 147},
            {0,   160, 132},
            {0,   142, 71},
            {0,   185, 0},
            {129, 204, 0},
            {139, 233, 0}     // Period 8
    };

    point_copy_coordinates_from_pixel(&point, *px);

    fractal_data_get_calculated_point(fractal_data, point, &calculated_point);

    if (calculated_point.period >= 1 && calculated_point.period <= 8) {
        pixel_set_color(px, period_color_map[calculated_point.period - 1]);
        return;
    }

    if (calculated_point.is_inside) {
        pixel_set_color(px, black);
        return;
    }

    pixel_set_color(px, white);
}