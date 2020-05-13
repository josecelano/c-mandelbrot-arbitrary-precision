#ifndef C_MANDELBROT_ARBITRARY_PRECISION_COLOR_H
#define C_MANDELBROT_ARBITRARY_PRECISION_COLOR_H

#define RBG_COLOR_SIZE sizeof(char) * 3

typedef char *rgb_color;

void set_color_for_pixel(
        char *color,
        int x, int y,
        int width, int height,
        const char *inside_color, const char *outside_color,
        int *iterations_taken_matrix
);

#endif //C_MANDELBROT_ARBITRARY_PRECISION_COLOR_H
