#ifndef C_MANDELBROT_ARBITRARY_PRECISION_IMAGE_H
#define C_MANDELBROT_ARBITRARY_PRECISION_IMAGE_H

void set_pixel_color(
        char *color,
        int x, int y,
        int width, int height, int *iterations_taken_matrix
);

#endif //C_MANDELBROT_ARBITRARY_PRECISION_IMAGE_H
