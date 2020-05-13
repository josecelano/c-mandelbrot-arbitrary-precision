#include <string.h>
#include <stdio.h>

#include "color.h"
#include "fractal.h"
#include "image.h"
#include "set.h"

void set_pixel_color(
        char *color,
        int x, int y,
        int width, int height, int *iterations_taken_matrix
) {
    int num_iter_for_pixel;

    num_iter_for_pixel = get_iterations_taken_for_point(x, y, width, height, iterations_taken_matrix);

    color_pixel_with_black_and_white_color_map(color, num_iter_for_pixel, iterations_taken_matrix);
}