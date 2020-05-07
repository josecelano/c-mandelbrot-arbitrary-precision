#ifndef C_MANDELBROT_ARBITRARY_PRECISION_COMPLEX_H
#define C_MANDELBROT_ARBITRARY_PRECISION_COMPLEX_H

#include "acb.h"

struct complex_dto {
    const char *re;
    const char *im;
};

void complex_set_from_re_im_str(acb_t z, const char *re_str, const char *im_str, slong prec);

void acb_set_from_re_im(acb_t z, const arb_t re, const arb_t im);

/**
 * Sets re_abs to the absolute value of real part and im_abs to the absolute value of imaginary part
 * of a complex number.
 */
void acb_abs_re_im(arb_t re_abs, arb_t im_abs, acb_t c);

/**
 * Sets re_abs to the absolute value of real part of a complex number.
 */
void acb_abs_re(arb_t re_abs, acb_t c);

/**
 * Sets im_abs to the absolute value of imaginary part of a complex number.
 */
void acb_abs_im(arb_t im_abs, acb_t c);

#endif //C_MANDELBROT_ARBITRARY_PRECISION_COMPLEX_H