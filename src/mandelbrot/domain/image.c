#include <string.h>
#include <stdio.h>

#include "color.h"
#include "fractal.h"
#include "image.h"
#include "set.h"

void set_pixel_color(char *color, int x, int y, fractal_matrix iterations_taken_matrix) {
    color_pixel_with_black_and_white_color_map(color, x, y, iterations_taken_matrix);
}