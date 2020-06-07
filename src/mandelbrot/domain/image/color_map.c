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
    rgb_color period_color_map[20] = {
            {60,  63,  104},    // Period 1
            {37,  62,  141},    // Period 2
            {0,   127, 147},    // Period 3
            {0,   160, 132},    // Period 4
            {0,   142, 71},     // Period 5
            {0,   185, 0},      // Period 6
            {129, 204, 0},      // Period 7
            {139, 233, 0},      // Period 8
            // Gradient grey/black for greater periods than 8
            {110, 110, 110},    // Period 9
            {100, 100, 100},    // Period 10
            {90,  90,  90},     // Period 11
            {80,  80,  80},     // Period 12
            {70,  70,  70},     // Period 13
            {60,  60,  60},     // Period 14
            {50,  50,  50},     // Period 15
            {40,  40,  40},     // Period 16
            {30,  30,  30},     // Period 17
            {20,  20,  20},     // Period 18
            {10,  10,  10},     // Period 19
            {0,   0,   0}       // Period 20
    };

    point_copy_coordinates_from_pixel(&point, *px);

    fractal_data_get_calculated_point(fractal_data, point, &calculated_point);

    if (calculated_point.period >= 1 && calculated_point.period <= 20) {
        pixel_set_color(px, period_color_map[calculated_point.period - 1]);
        return;
    }

    if (calculated_point.is_inside) {
        pixel_set_color(px, black);
        return;
    }

    pixel_set_color(px, white);
}

void get_color_map_name(char *color_map_name, color_map_t color_map) {
    switch (color_map) {
        case CM_BLACK_ON_WHITE:
            strcpy(color_map_name, "black-on-white");
            break;
        case CM_WHITE_ON_BLACK:
            strcpy(color_map_name, "white-on-black");
            break;
        case CM_COLORED_PERIODS:
            strcpy(color_map_name, "colored-periods");
            break;
        default:
            printf("Exception. Invalid color map %d\n", color_map);
            abort();
    }
}