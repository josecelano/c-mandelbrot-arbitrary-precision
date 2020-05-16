#include "acb.h"
#include "arb.h"
#include "complex.h"
#include "formula.h"
#include "set.h"
#include "zpoint.h"

int mandelbrot_set_contains(zpoint point, int max_iterations, slong prec) {
    int iterations_taken;

    iterations_taken = mandelbrot_set_calculate_num_iterations_for(point, max_iterations, prec);

    if (iterations_taken == MAX_ITERATIONS) {
        return INSIDE;
    }

    return OUTSIDE;
}

int is_value_a_inside_point(int num_iter_for_pixel) {
    if (num_iter_for_pixel == MAX_ITERATIONS) {
        return INSIDE;
    }

    return OUTSIDE;
}

int mandelbrot_set_calculate_num_iterations_for(zpoint point, int max_iterations, slong prec) {

    int inside = 0, i, num_iter = MAX_ITERATIONS;
    acb_t c, zero, z, f;

    acb_init(c);

    acb_set_from_re_im(c, point.re, point.im);

    if (!inside_main_cardioid(c, prec)) {

        // Execute iterations

        acb_init(zero);
        acb_init(z);
        acb_init(f);

        for (i = 1; i <= max_iterations; ++i) {
            mandelbrot_formula(f, z, c, prec);

            if (bailout(f, prec)) {
                num_iter = i;
                break;
                return i;
            }

            acb_set(z, f);
        }

        acb_clear(zero);
        acb_clear(z);
        acb_clear(f);
    }

    acb_clear(c);

    return num_iter;
}

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

int inside_main_cardioid(acb_t c, slong prec) {
    int ret = 0;
    arb_t x, y;           // Real and imaginary parts
    arb_t a, b;           // Left and right side of the comparison operation
    arb_t q;              // Variable in the formula
    arb_t temp;           // Temporal results and constants in the formula
    arb_t _x_minus_0_25;  // x - 1/4
    arb_t _0_25;          // 1/4
    arb_t y_sqr;          // y²

    arb_init(x);
    arb_init(y);

    arb_init(a);
    arb_init(b);

    arb_init(q);

    arb_init(temp);
    arb_init(_x_minus_0_25);
    arb_init(_0_25);
    arb_init(y_sqr);

    // Set formula constants
    arb_set_str(_0_25, "0.25", prec);

    // Get real and imaginary parts
    acb_get_real(x, c);
    acb_get_imag(y, c);

    /**  Calculate variable q **/

    // _x_minus_0_25 = x - 1/4
    arb_sub(_x_minus_0_25, x, _0_25, prec);
    // temp = (x - 1/4)²
    arb_sqr(temp, _x_minus_0_25, prec);
    // y²
    arb_sqr(y_sqr, y, prec);

    // q = (x - 1/4)² + y²
    arb_add(q, temp, y_sqr, prec);

    /**  Calculate a (left side of comparison) **/

    // temp = q + (x - 1/4)
    arb_add(temp, q, _x_minus_0_25, prec);
    // a = q * (q + (x - 1/4))
    arb_mul(a, q, temp, prec);

    /**  Calculate b (right side of comparison) **/

    // b = 1/4 * y²
    arb_mul(b, _0_25, y_sqr, prec);

    // a < b
    if (arb_lt(a, b)) {
        ret = 1;
    }

    arb_clear(x);
    arb_clear(y);

    arb_clear(a);
    arb_clear(b);

    arb_clear(q);

    arb_clear(temp);
    arb_clear(_x_minus_0_25);
    arb_clear(_0_25);
    arb_clear(y_sqr);

    return ret;
}