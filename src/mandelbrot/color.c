#include <string.h>
#include <stdio.h>

#include "color.h"
#include "image.h"
#include "set.h"

/**
 * Iteration taken matrix is flipped horizontally, that's is to say y pixel coordinates increase from bottom to top.
 * For standard graphics format (used in PPM format) (0,0) pixel coordinates is the left top corner of the image.
 */
int get_iterations_taken_for_pixel(int x, int y, int width, int height, int *iterations_taken_matrix) {
    return iterations_taken_matrix[(height - 1 - y) * width + x];
}

void set_color_for_pixel(
        rgb_color color,
        int x, int y,
        int width, int height,
        const char *inside_color, const char *outside_color,
        int *iterations_taken_matrix
) {
    int num_iter_for_pixel;

    num_iter_for_pixel = get_iterations_taken_for_pixel(x, y, width, height, iterations_taken_matrix);

    if (num_iter_for_pixel == MAX_ITERATIONS) {
        strncpy(color, inside_color, RBG_COLOR_SIZE);
    } else {
        strncpy(color, outside_color, RBG_COLOR_SIZE);
    }
}