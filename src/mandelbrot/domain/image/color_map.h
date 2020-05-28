#ifndef C_MANDELBROT_ARBITRARY_PRECISION_COLOR_MAP_H
#define C_MANDELBROT_ARBITRARY_PRECISION_COLOR_MAP_H

#include "../fractal_data.h"
#include "./pixel.h"

typedef enum {
    BLACK_ON_WHITE = 0,
    WHITE_ON_BLACK = 1,
    CM_COLORED_PERIODS = 2, // A different color for each point inside where a period was detected (period detection)
} color_map_t;

void color_pixel_with_black_on_white_color_map(pixel *px, fractal_data_t fractal_data);

void color_pixel_with_white_on_black_color_map(pixel *px, fractal_data_t fractal_data);

void color_pixel_with_periods_color_map(pixel *px, fractal_data_t fractal_data);

#endif //C_MANDELBROT_ARBITRARY_PRECISION_COLOR_MAP_H
