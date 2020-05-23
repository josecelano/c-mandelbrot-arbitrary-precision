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

void complex_set_from_dto(acb_t z, complex_dto dto, slong prec) {
    complex_set_from_re_im_str(z, dto.re, dto.im, prec);
}

void acb_set_from_zpoint(acb_t z, zpoint point) {
    acb_set_arb_arb(z, point.re, point.im);
}

void zpoint_set_from_complex_dto(zpoint *c, complex_dto dto, slong prec) {
    zpoint_set_from_re_im_str(c, dto.re, dto.im, prec);
}