#include "acb.h"
#include "complex.h"

void complex_set_from_re_im_str(acb_t z, const char * re_str, const char * im_str, slong prec) {
    arb_t re,im;

    arb_init(re);
    arb_init(im);

    arb_set_str(re, re_str, prec);
    arb_set_str(im, im_str, prec);

    acb_set_arb_arb(z, re, im);

    arb_clear(re);
    arb_clear(im);
}

void acb_set_from_re_im(acb_t z, const arb_t re, const arb_t im) {
    acb_set_arb_arb(z, re, im);
}