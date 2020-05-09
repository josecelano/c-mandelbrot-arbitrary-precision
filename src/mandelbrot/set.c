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

/**
 * Bailout formula:
 * Zx²+Zy² < ER²
 * https://en.wikibooks.org/wiki/Fractals/Iterations_in_the_complex_plane/Mandelbrot_set/mandelbrot#Bailout_test
 * @param c
 * @param prec
 * @return
 */
int bailout(acb_t c, slong prec) {

    int ret = 0;
    arb_t re, im, re_sqr, im_sqr, total, escape_radius_square;

    arb_init(re);
    arb_init(im);
    arb_init(re_sqr);
    arb_init(im_sqr);
    arb_init(total);
    arb_init(escape_radius_square);

    arb_set_str(escape_radius_square, "4", prec);

    // Get real and imaginary parts
    acb_get_real(re, c);
    acb_get_imag(im, c);

    arb_sqr(re_sqr, re, prec); // zx * zx
    arb_sqr(im_sqr, im, prec); // zy * zy

    arb_add(total, re_sqr, im_sqr, prec);

    if (arb_gt(total, escape_radius_square)) {
        ret = 1;
    }

    arb_clear(re);
    arb_clear(im);
    arb_clear(re_sqr);
    arb_clear(im_sqr);
    arb_clear(total);
    arb_clear(escape_radius_square);

    return ret;
}