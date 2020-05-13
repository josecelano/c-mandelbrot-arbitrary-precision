#include <string.h>
#include <stdio.h>

#include "color.h"
#include "set.h"

void color_pixel_with_black_and_white_color_map(
        rgb_color color,
        int num_iter_for_pixel,
        int *iterations_taken_matrix
) {
    const char black[3] = {0, 0, 0};
    const char white[3] = {255, 255, 255};

    if (num_iter_for_pixel == MAX_ITERATIONS) {
        strncpy(color, black, RBG_COLOR_SIZE);
    } else {
        strncpy(color, white, RBG_COLOR_SIZE);
    }
}