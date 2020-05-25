#include "pixel.h"

void pixel_set_coordinates(pixel *px, int x, int y) {
    px->x = x;
    px->y = y;
}

void pixel_set_color(pixel *px, rgb_color color) {
    px->color = color;
}
