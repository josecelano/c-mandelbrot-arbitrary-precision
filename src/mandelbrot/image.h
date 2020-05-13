#ifndef C_MANDELBROT_ARBITRARY_PRECISION_IMAGE_H
#define C_MANDELBROT_ARBITRARY_PRECISION_IMAGE_H

#include "color.h"
#include "fractal.h"

void render_and_write_out_image(char *filename, fractal_resolution resolution, int *iterations_taken_matrix);

void set_pixel_color(
        rgb_color color,
        int x, int y,
        int width, int height, int *iterations_taken_matrix
);

/**
 * Iteration taken matrix is flipped horizontally, that's is to say y pixel coordinates increase from bottom to top.
 * For standard graphics format (used in PPM format) (0,0) pixel coordinates is the left top corner of the image.
 */
int get_iterations_taken_for_point(
        int x, int y,
        int width, int height, int *iterations_taken_matrix
);

#endif //C_MANDELBROT_ARBITRARY_PRECISION_IMAGE_H
