#include <string.h>
#include <stdio.h>

#include "color.h"
#include "../fractal.h"
#include "image.h"
#include "../set.h"

/**
 * TODO: Move color to pixel struct and pass only pixel px
 */
void set_pixel_color(char *color, pixel px, fractal_matrix iterations_taken_matrix) {
    color_pixel_with_black_and_white_color_map(color, px, iterations_taken_matrix);
}