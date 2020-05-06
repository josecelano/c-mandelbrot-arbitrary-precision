#ifndef C_MANDELBROT_ARBITRARY_PRECISION_ZPOINT_H
#define C_MANDELBROT_ARBITRARY_PRECISION_ZPOINT_H

#include "acb.h"

typedef struct {
    arb_t re;
    arb_t im;
} zpoint;

void zpoint_init(zpoint *c);

void zpoint_clean(zpoint *c);

void zpoint_set(zpoint *y, zpoint *x);

void zpoint_set_from_re_im_str(zpoint *c, const char *re, const char *im, slong prec);

void zpoint_set_from_re_im(zpoint *c, const arb_t re, const arb_t im);

void zpoint_set_re(zpoint *c, const arb_t re);

void zpoint_add(zpoint *z, zpoint x, zpoint y, slong prec);

#endif //C_MANDELBROT_ARBITRARY_PRECISION_ZPOINT_H