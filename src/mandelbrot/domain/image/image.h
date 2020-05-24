#ifndef C_MANDELBROT_ARBITRARY_PRECISION_IMAGE_H
#define C_MANDELBROT_ARBITRARY_PRECISION_IMAGE_H

#include "../fractal.h"
#include "../point.h"
#include "./color_map.h"

void set_pixel_color(pixel *px, fractal_matrix iterations_taken_matrix, color_map_name color_map);

#endif //C_MANDELBROT_ARBITRARY_PRECISION_IMAGE_H
