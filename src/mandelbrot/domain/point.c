#include "point.h"

void point_set(point_t *p, int x, int y) {
    p->x = x;
    p->y = y;
}

void point_set_from_pixel(point_t *p, pixel px) {
    p->x = px.x;
    p->y = px.y;
}