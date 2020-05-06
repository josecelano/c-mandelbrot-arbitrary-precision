#include "acb.h"
#include "arb.h"
#include "complex.h"
#include "formula.h"
#include "set.h"
#include "zpoint.h"

int mandelbrot_set_contains(zpoint point, int max_iterations, slong prec) {

    int i;
    acb_t c, zero, z, f;
    arb_t re, im, re_abs, im_abs, two;

    acb_init(c);
    acb_init(zero);
    acb_init(z);
    acb_init(f);

    arb_init(re);
    arb_init(im);
    arb_init(re_abs);
    arb_init(im_abs);
    arb_init(two);

    acb_set_from_re_im(c, point.re, point.im);
    arb_set_str(two, "2", prec);

    for (i = 0; i < max_iterations; ++i)
    {
        mandelbrot_formula(f, z, c, prec);

        // Get real and imaginary parts
        acb_get_real(re, z);
        acb_get_imag(im, z);

        // Get absolute value of real and imaginary parts
        arb_abs(re_abs, re);
        arb_abs(im_abs, im);

//        // DEBUG
//        flint_printf("iter: %d\n", i);
//        flint_printf("re_abs = "); arb_printn(re_abs, 10, 0); flint_printf("\n");
//        flint_printf("im_abs = "); arb_printn(im_abs, 10, 0); flint_printf("\n");

        if (arb_gt(re_abs, two)) {
            return i;
        }

        if (arb_gt(im_abs, two)) {
            return i;
        }

        acb_set(z, f);
    }

    acb_clear(c);
    acb_clear(zero);
    acb_clear(z);
    acb_clear(f);

    arb_clear(re);
    arb_clear(im);
    arb_clear(re_abs);
    arb_clear(im_abs);
    arb_clear(two);

    return MAX_ITERATIONS;
}