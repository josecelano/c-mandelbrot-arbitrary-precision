#include "acb.h"
#include "arb.h"
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

void acb_abs_re_im(arb_t re_abs, arb_t im_abs, acb_t c) {
    acb_abs_re(re_abs, c);
    acb_abs_im(im_abs, c);
}

void acb_abs_re(arb_t re_abs, acb_t c) {
    arb_t re;

    arb_init(re);

    // Get real part
    acb_get_real(re, c);

    // Get absolute value of real parts
    arb_abs(re_abs, re);

    arb_clear(re);
}

void acb_abs_im(arb_t im_abs, acb_t c) {
    arb_t im;

    arb_init(im);

    // Get imaginary part
    acb_get_imag(im, c);

    // Get absolute value of imaginary part
    arb_abs(im_abs, im);

    arb_clear(im);
}