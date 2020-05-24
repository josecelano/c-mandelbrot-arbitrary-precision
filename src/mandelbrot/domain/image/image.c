#include <string.h>
#include <stdio.h>

#include "../fractal.h"
#include "../set.h"
#include "./color.h"
#include "./image.h"
#include "color_map.h"

/**
 * TODO: Move color to pixel struct and pass only pixel px
 */
void set_pixel_color(char *color, pixel px, fractal_matrix iterations_taken_matrix) {
    color_pixel_with_black_and_white_color_map(color, px, iterations_taken_matrix);
}