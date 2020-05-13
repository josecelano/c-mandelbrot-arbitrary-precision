#ifndef C_MANDELBROT_ARBITRARY_PRECISION_FORMULA_H
#define C_MANDELBROT_ARBITRARY_PRECISION_FORMULA_H

#include "acb.h"

/**
 * It returns: z² + c
 */
void mandelbrot_formula(acb_t result, acb_t z, acb_t c, slong prec);

#endif //C_MANDELBROT_ARBITRARY_PRECISION_FORMULA_H