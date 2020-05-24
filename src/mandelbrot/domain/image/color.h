#ifndef C_MANDELBROT_ARBITRARY_PRECISION_COLOR_H
#define C_MANDELBROT_ARBITRARY_PRECISION_COLOR_H

#include "../fractal.h"
#include "pixel.h"

#define RBG_COLOR_SIZE sizeof(char) * 3

typedef char *rgb_color;

void color_pixel_with_black_and_white_color_map(rgb_color color, pixel px, fractal_matrix iterations_taken_matrix);

#endif //C_MANDELBROT_ARBITRARY_PRECISION_COLOR_H
