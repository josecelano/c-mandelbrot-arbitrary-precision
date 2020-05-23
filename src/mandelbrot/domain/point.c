#include "point.h"

void point_set(point *p, int x, int y) {
    p->x = x;
    p->y = y;
}

void point_set_from_pixel(point *p, pixel px) {
    p->x = px.x;
    p->y = px.y;
}