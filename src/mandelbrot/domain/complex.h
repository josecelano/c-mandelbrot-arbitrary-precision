#ifndef C_MANDELBROT_ARBITRARY_PRECISION_COMPLEX_H
#define C_MANDELBROT_ARBITRARY_PRECISION_COMPLEX_H

#include "acb.h"

typedef struct {
    const char *re;
    const char *im;
} complex_dto;

void complex_set_from_re_im_str(acb_t z, const char *re_str, const char *im_str, slong prec);

void complex_set_from_complex_dto(acb_t z, complex_dto dto, slong prec);

void acb_set_from_re_im(acb_t z, const arb_t re, const arb_t im);

#endif //C_MANDELBROT_ARBITRARY_PRECISION_COMPLEX_H