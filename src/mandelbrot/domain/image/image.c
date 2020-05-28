#include <string.h>
#include <stdio.h>

#include "../fractal.h"
#include "../set.h"
#include "./color.h"
#include "./color_map.h"
#include "./image.h"

void set_pixel_color(pixel *px, fractal_data_t fractal_data, color_map_t color_map) {
    switch (color_map) {
        case BLACK_ON_WHITE:
            color_pixel_with_black_on_white_color_map(px, fractal_data);
            break;
        case WHITE_ON_BLACK:
            color_pixel_with_white_on_black_color_map(px, fractal_data);
            break;
        case CM_COLORED_PERIODS:
            color_pixel_with_periods_color_map(px, fractal_data);
            break;
        default:
            color_pixel_with_black_on_white_color_map(px, fractal_data);
    }
}