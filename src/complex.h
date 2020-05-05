#ifndef C_MANDELBROT_ARBITRARY_PRECISION_COMPLEX_H
#define C_MANDELBROT_ARBITRARY_PRECISION_COMPLEX_H

#include "acb.h"

struct complex_dto {
    const char *re;
    const char *im;
};

/**
 * Create complex from strings real and imaginary parts in string type.
 */
void complex_set_from_str(acb_t z, const char *re_str, const char *im_str, slong prec);

/**
 * It creates a complex from real and imaginary parts in arb_t (real arbitrary precision) type.
 */
void complex_set_from_re_im(acb_t z, const arb_t re, const arb_t im);

#endif //C_MANDELBROT_ARBITRARY_PRECISION_COMPLEX_H