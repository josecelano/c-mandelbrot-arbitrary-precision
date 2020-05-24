#ifndef C_MANDELBROT_ARBITRARY_PRECISION_ZPOINT_H
#define C_MANDELBROT_ARBITRARY_PRECISION_ZPOINT_H

#include "arb.h"

typedef struct {
    arb_t re;
    arb_t im;
} zpoint_t;

void zpoint_init(zpoint_t *c);

void zpoint_clean(zpoint_t *c);

void zpoint_set(zpoint_t *y, zpoint_t *x);

void zpoint_set_from_re_im_str(zpoint_t *c, const char *re, const char *im, slong prec);

void zpoint_set_from_re_im(zpoint_t *c, const arb_t re, const arb_t im);

void zpoint_set_re(zpoint_t *c, const arb_t re);

void zpoint_add(zpoint_t *z, zpoint_t x, zpoint_t y, slong prec);

#endif //C_MANDELBROT_ARBITRARY_PRECISION_ZPOINT_H