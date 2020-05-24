#ifndef C_MANDELBROT_ARBITRARY_PRECISION_COMPLEX_H
#define C_MANDELBROT_ARBITRARY_PRECISION_COMPLEX_H

#include "acb.h"

#include "zpoint.h"

typedef struct {
    const char *re;
    const char *im;
} complex_dto_t;

void complex_set_from_re_im_str(acb_t z, const char *re_str, const char *im_str, slong prec);

void complex_set_from_dto(acb_t z, complex_dto_t dto, slong prec);

void acb_set_from_zpoint(acb_t z, zpoint_t point);

void zpoint_set_from_complex_dto(zpoint_t *c, complex_dto_t dto, slong prec);

#endif //C_MANDELBROT_ARBITRARY_PRECISION_COMPLEX_H