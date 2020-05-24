#ifndef C_MANDELBROT_ARBITRARY_PRECISION_COLOR_MAP_H
#define C_MANDELBROT_ARBITRARY_PRECISION_COLOR_MAP_H

#include "../fractal.h"
#include "./pixel.h"

typedef enum {
    BLACK_ON_WHITE = 0,
    WHITE_ON_BLACK = 1,
} color_map_name;

void color_pixel_with_black_on_white_color_map(pixel *px, fractal_data_t fractal_data);

void color_pixel_with_white_on_black_color_map(pixel *px, fractal_data_t fractal_data);

#endif //C_MANDELBROT_ARBITRARY_PRECISION_COLOR_MAP_H
