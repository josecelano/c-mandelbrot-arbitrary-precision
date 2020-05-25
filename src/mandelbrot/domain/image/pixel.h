#ifndef C_MANDELBROT_ARBITRARY_PRECISION_PIXEL_H
#define C_MANDELBROT_ARBITRARY_PRECISION_PIXEL_H

#include "./color.h"

typedef struct {
    int x;
    int y;
    rgb_color color;
} pixel;

void pixel_set_coordinates(pixel *px, int x, int y);

void pixel_set_color(pixel *px, rgb_color color);

#endif //C_MANDELBROT_ARBITRARY_PRECISION_PIXEL_H
