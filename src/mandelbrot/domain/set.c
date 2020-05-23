#include "acb.h"
#include "arb.h"

#include "../infrastructure/console.h"
#include "../presentation/output.h"
#include "./complex.h"
#include "./formula.h"
#include "./optimisation/main_cardioid_detection.h"
#include "./optimisation/period2_detection.h"
#include "./optimisation/periodicity_checking.h"
#include "./set.h"
#include "./zpoint.h"

int mandelbrot_set_contains(zpoint point, int max_iterations, app_config config) {
    int inside, iterations_taken, period;

    mandelbrot_set_calculate_point(
            point, max_iterations, config,
            &inside, &iterations_taken, &period
    );

    return inside;
}

int is_value_a_inside_point(int num_iter_for_pixel) {
    if (num_iter_for_pixel == MAX_ITERATIONS) {
        return INSIDE;
    }

    return OUTSIDE;
}

void execute_iterations_with_period_checking(
        acb_t c, int max_iterations, app_config config,
        int *inside, int *iterations_taken, int *period) {
    int i;
    acb_t f, z;

    *inside = INSIDE;
    *iterations_taken = 0;
    *period = 0;

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
    arb_set_str(old_re, "0.0", config.precision);
    arb_set_str(old_im, "0.0", config.precision);

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
    arb_set_str(period_tolerance, "0", config.precision);           // Period checking disabled
    arb_set_str(period_tolerance, "1e-9", config.precision);        // Initial value for Gnofract4D
    arb_set_str(period_tolerance, "1e-17", config.precision);       // Some samples use this value
    arb_set_str(period_tolerance, "0.000000001", config.precision); // With this value we reach max iter
    arb_set_str(period_tolerance, "0.00000001", config.precision);  // Iter 35.
    arb_set_str(period_tolerance, "0.0015625", config.precision);   // Iter 14.   4/256/10 = 0,015625

    for (i = 1; i <= max_iterations; ++i) {

        *iterations_taken = i;

        mandelbrot_formula(f, z, c, config.precision);

        if (app_config_verbose_option_enabled(config, PRINT_ITERATIONS)) {
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

        if (bailout(f, config.precision)) {
            *inside = OUTSIDE;
            break;
        }

        acb_set(z, f);

        // Periodicity check

        // Get real and imaginary parts
        acb_get_real(z_re, z);
        acb_get_imag(z_im, z);

        // Check for period
        int period_found = check_for_period(i, c, z_re, z_im, old_re, old_im, period_tolerance, check_counter, config);

        if (period_found) {
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

            if (app_config_verbose_option_enabled(config, PRINT_PERIODS)) {
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
}

void mandelbrot_set_calculate_point(
        zpoint point, int max_iterations, app_config config,
        int *inside, int *iterations_taken, int *period
) {
    acb_t c;

    *inside = INSIDE;
    *iterations_taken = 0;
    *period = 0;

    acb_init(c);

    acb_set_from_zpoint(c, point);

    if (inside_main_cardioid(c, config)) {
        *period = 1;
        acb_clear(c);
        return;
    }

    if (inside_period_2_bulb(c, config)) {
        *period = 2;
        acb_clear(c);
        return;
    }

    execute_iterations_with_period_checking(c, max_iterations, config, inside, iterations_taken, period);

    acb_clear(c);
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