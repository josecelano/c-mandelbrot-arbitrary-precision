#ifndef C_MANDELBROT_ARBITRARY_PRECISION_POINT_H
#define C_MANDELBROT_ARBITRARY_PRECISION_POINT_H

#include "image/pixel.h"

typedef struct {
    int x;
    int y;
} point_t;

void point_set_coordinates(point_t *p, int x, int y);

void point_copy_coordinates_from_pixel(point_t *p, pixel px);

#endif //C_MANDELBROT_ARBITRARY_PRECISION_POINT_H
