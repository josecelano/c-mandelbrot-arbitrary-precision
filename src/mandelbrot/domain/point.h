#ifndef C_MANDELBROT_ARBITRARY_PRECISION_POINT_H
#define C_MANDELBROT_ARBITRARY_PRECISION_POINT_H

#include "image/pixel.h"

typedef struct {
    int x;
    int y;
} point;

void point_set(point *p, int x, int y);

void point_set_from_pixel(point *p, pixel px);

#endif //C_MANDELBROT_ARBITRARY_PRECISION_POINT_H
