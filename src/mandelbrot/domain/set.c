#include "acb.h"
#include "arb.h"

#include "complex.h"
#include "formula.h"
#include "set.h"
#include "zpoint.h"

#include "../presentation/output.h"
#include "../infrastructure/console.h"

int mandelbrot_set_contains(zpoint point, int max_iterations, slong prec, int print_periods) {
    int iterations_taken;

    iterations_taken = mandelbrot_set_calculate_num_iterations_for(point, max_iterations, prec, print_periods);

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

/**
 * It return 1 if period is found
 */
int check_for_period(
        int iter,
        acb_t c,
        arb_t z_re, arb_t z_im,
        arb_t old_re, arb_t old_im,
        arb_t period_tolerance,
        int check_counter,
        slong prec,
        int print_periods,
        int print_iterations
) {
    int ret = 0;

    arb_t re_diff, im_diff;

    arb_init(re_diff);
    arb_init(im_diff);

    // re_diff = abs(re - h_re)
    arb_sub(re_diff, z_re, old_re, prec);
    arb_abs(re_diff, re_diff);

    // im_diff = abs(im - h_im)
    arb_sub(im_diff, z_im, old_im, prec);
    arb_abs(im_diff, im_diff);

    if (print_periods) {
        print_period_checking(re_diff, im_diff);
    }

    if (arb_lt(re_diff, period_tolerance) && arb_lt(im_diff, period_tolerance)) {
        // Period found
        if (print_periods) {
            print_period_found(check_counter, iter);
        }
        ret = 1;
    }

    arb_clear(re_diff);
    arb_clear(im_diff);

    return ret;
}

int execute_iterations(acb_t c, int max_iterations, slong prec, int print_periods, int print_iterations, int *period) {
    int i, num_iter = MAX_ITERATIONS;
    acb_t f, z;

    acb_init(f);
    acb_init(z);

    int check = 1;
    int check_counter = 0;

    int update = 10;
    int update_counter = 0;

    arb_t z_re, z_im;

    // Period checking
    arb_t old_re, old_im;
    arb_t period_tolerance;

    arb_init(z_re);
    arb_init(z_im);

    // Period checking
    arb_init(old_re);
    arb_init(old_im);
    arb_init(period_tolerance);

    // Period checking
    arb_set_str(old_re, "0.0", prec);
    arb_set_str(old_im, "0.0", prec);

    // TODO:
    // * We need to know how to calculate the period tolerance
    // * And only apply period checking after a minimum number of iterations
    // See other examples:
    // * https://github.com/HyveInnovate/gnofract4d/blob/master/examples/cpp/custom_mandelbrot_formula.c#L356-L389
    // * https://github.com/josch/mandelbrot/blob/master/mandel_mpfr.c#L109-L133
    //
    // I think this is the algorithm used but we need need the position of the first cycle:
    // https://en.wikipedia.org/wiki/Cycle_detection#Brent's_algorithm
    //
    // Testing different tolerances ...
    arb_set_str(period_tolerance, "0", prec);           // Period checking disabled
    arb_set_str(period_tolerance, "1e-9", prec);        // Initial value for Gnofract4D
    arb_set_str(period_tolerance, "1e-17", prec);       // Some samples use this value
    arb_set_str(period_tolerance, "0.000000001", prec); // With this value we reach max iter
    arb_set_str(period_tolerance, "0.00000001", prec);  // Iter 35.
    arb_set_str(period_tolerance, "0.0015625", prec);   // Iter 14.   4/256/10 = 0,015625

    *period = 0;

    for (i = 1; i <= max_iterations; ++i) {

        mandelbrot_formula(f, z, c, prec);

        if (print_iterations) {
            // Print iteration
            print_loop_iteration(
                    i,
                    check, check_counter, update, update_counter,
                    f, z, c,
                    z_re, z_im,
                    old_re, old_im,
                    period_tolerance
            );
        }

        if (bailout(f, prec)) {
            num_iter = i;
            break;
        }

        acb_set(z, f);

        // Periodicity check

        // Get real and imaginary parts
        acb_get_real(z_re, z);
        acb_get_imag(z_im, z);

        // Check for period
        int period_found = check_for_period(i, c, z_re, z_im, old_re, old_im, period_tolerance, check_counter, prec,
                                            print_periods, print_iterations);

        if (period_found) {
            num_iter = MAX_ITERATIONS;
            *period = check_counter;
            break;
        }
        // End check for period

        // Update history
        if (check == check_counter) {
            check_counter = 0;

            // Double the value of check
            if (update == update_counter) {
                update_counter = 0;
                check <<= 1; // check * 2
            }
            update_counter++;

            if (print_periods) {
                console_printf("->update old\n");
            }

            arb_set(old_re, z_re);
            arb_set(old_im, z_im);
        }
        // End of update history
        check_counter++;

        // End periodicity check
    }

    arb_clear(z_re);
    arb_clear(z_im);
    arb_clear(old_re);
    arb_clear(old_im);

    arb_clear(period_tolerance);

    acb_clear(f);
    acb_clear(z);

    return num_iter;
}

int mandelbrot_set_calculate_num_iterations_for(zpoint point, int max_iterations, slong prec, int print_periods) {

    int inside = 0, i, num_iter = MAX_ITERATIONS;
    acb_t c;

    acb_init(c);

    acb_set_from_zpoint(c, point);

    if (inside_main_cardioid(c, prec)) {
        acb_clear(c);
        return MAX_ITERATIONS;
    }

    if (inside_period_2_bulb(c, prec)) {
        acb_clear(c);
        return MAX_ITERATIONS;
    }

    int print_iterations = 0;
    int period;

    num_iter = execute_iterations(c, max_iterations, prec, print_periods, print_iterations, &period);

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

int inside_period_2_bulb(acb_t c, slong prec) {
    int ret = 0;
    arb_t x, y;           // Real and imaginary parts
    arb_t temp;           // Temporal results and constants in the formula
    arb_t _1;             // 1
    arb_t _0_0625;        // 1/16 = 0.0625
    arb_t y_sqr;          // y²

    arb_init(x);
    arb_init(y);
    arb_init(temp);
    arb_init(_1);
    arb_init(_0_0625);
    arb_init(y_sqr);

    // Set formula constants
    arb_set_str(_0_0625, "0.0625", prec);
    arb_set_str(_1, "1", prec);

    // Get real and imaginary parts
    acb_get_real(x, c);
    acb_get_imag(y, c);

    /**  Calculate left side of comparison **/

    // temp = x + 1
    arb_add(temp, x, _1, prec);
    // temp = (x + 1)²
    arb_sqr(temp, temp, prec);
    // y²
    arb_sqr(y_sqr, y, prec);
    // temp = (x + 1)² + y²
    arb_add(temp, temp, y_sqr, prec);

    // temp < 1/16
    if (arb_lt(temp, _0_0625)) {
        ret = 1;
    }

    arb_clear(x);
    arb_clear(y);
    arb_clear(temp);
    arb_clear(_1);
    arb_clear(_0_0625);
    arb_clear(y_sqr);

    return ret;
}