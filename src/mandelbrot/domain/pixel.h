#ifndef C_MANDELBROT_ARBITRARY_PRECISION_PIXEL_H
#define C_MANDELBROT_ARBITRARY_PRECISION_PIXEL_H

typedef struct {
    int x;
    int y;
} pixel;

void pixel_set(pixel *px, int x, int y);

#endif //C_MANDELBROT_ARBITRARY_PRECISION_PIXEL_H
