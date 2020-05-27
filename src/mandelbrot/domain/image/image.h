#ifndef C_MANDELBROT_ARBITRARY_PRECISION_IMAGE_H
#define C_MANDELBROT_ARBITRARY_PRECISION_IMAGE_H

#include "../fractal.h"
#include "../point.h"
#include "./color_map.h"

void set_pixel_color(pixel *px, fractal_data_t fractal_data, color_map_t color_map);

#endif //C_MANDELBROT_ARBITRARY_PRECISION_IMAGE_H
