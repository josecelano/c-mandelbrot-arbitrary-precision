#include "acb.h"
#include "formula.h"

void mandelbrot_formula(acb_t result, acb_t z, acb_t c, slong prec) {

    // Temp variable
    acb_t t__square;

    acb_init(t__square);

    // z²
    acb_mul(t__square, z, z, prec);

    // z² + c
    acb_add(result, t__square, c, prec);

    acb_clear(t__square);
}