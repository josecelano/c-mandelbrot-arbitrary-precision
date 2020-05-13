#include "acb.h"
#include "zpoint.h"

void zpoint_init(zpoint *c) {
    arb_init(c->re);
    arb_init(c->im);
}

void zpoint_clean(zpoint *c) {
    arb_clear(c->re);
    arb_clear(c->im);
}

void zpoint_set(zpoint *y, zpoint *x) {
    arb_set(y->re, x->re);
    arb_set(y->im, x->im);
}

void zpoint_set_from_re_im_str(zpoint *c, const char *re, const char *im, slong prec) {
    arb_set_str(c->re, re, prec);
    arb_set_str(c->im, im, prec);
}

void zpoint_set_from_re_im(zpoint *c, const arb_t re, const arb_t im) {
    arb_set(c->re, re);
    arb_set(c->im, im);
}

void zpoint_set_re(zpoint *c, const arb_t re) {
    arb_set(c->re, re);
}

void zpoint_add(zpoint *z, zpoint x, zpoint y, slong prec) {
    arb_add(z->re, x.re, y.re, prec);
    arb_add(z->im, x.im, y.im, prec);
}