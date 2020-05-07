#include "acb.h"
#include "arb.h"
#include "complex.h"
#include "formula.h"
#include "set.h"
#include "zpoint.h"

int mandelbrot_set_contains(zpoint point, int max_iterations, slong prec) {

    int i, num_iter = MAX_ITERATIONS;
    acb_t c, zero, z, f;

    acb_init(c);
    acb_init(zero);
    acb_init(z);
    acb_init(f);

    acb_set_from_re_im(c, point.re, point.im);

    for (i = 0; i < max_iterations; ++i)
    {
        mandelbrot_formula(f, z, c, prec);

        if (bailout(f, prec)) {
            num_iter = i;
            break;
            return i;
        }

        acb_set(z, f);
    }

    acb_clear(c);
    acb_clear(zero);
    acb_clear(z);
    acb_clear(f);

    return num_iter;
}

int bailout(acb_t c, slong prec) {

    int ret = 0;
    arb_t re_abs, im_abs, two;

    arb_init(re_abs);
    arb_init(im_abs);
    arb_init(two);

    arb_set_str(two, "2", prec);

    acb_abs_re_im(re_abs, im_abs, c);

    if (arb_gt(re_abs, two) || arb_gt(im_abs, two)) {
        ret = 1;
    }

    arb_clear(re_abs);
    arb_clear(im_abs);
    arb_clear(two);

    return ret;
}