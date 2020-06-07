#include "arb.h"
#include "acb.h"

#include "../../application/config.h"
#include "../../infrastructure/user_interface/console/console_printer.h"
#include "../../presentation/output.h"
#include "../calculated_point.h"
#include "../formula.h"
#include "../fractal.h"
#include "../set.h"

int check_for_period(int iter, acb_t c, arb_t z_re, arb_t z_im, arb_t old_re, arb_t old_im, arb_t period_tolerance,
                     int check_counter, config_t *config) {
    int ret = 0;

    arb_t re_diff, im_diff;

    arb_init(re_diff);
    arb_init(im_diff);

    // re_diff = abs(re - h_re)
    arb_sub(re_diff, z_re, old_re, config->precision);
    arb_abs(re_diff, re_diff);

    // im_diff = abs(im - h_im)
    arb_sub(im_diff, z_im, old_im, config->precision);
    arb_abs(im_diff, im_diff);

    if (app_config_verbose_option_enabled(config, VO_PRINT_PERIODS)) {
        print_period_checking(re_diff, im_diff);
    }

    if (arb_lt(re_diff, period_tolerance) && arb_lt(im_diff, period_tolerance)) {
        // Period found
        if (app_config_verbose_option_enabled(config, VO_PRINT_PERIODS)) {
            print_period_found(check_counter, iter);
        }
        ret = 1;
    }

    arb_clear(re_diff);
    arb_clear(im_diff);

    return ret;
}

void execute_iterations_with_period_checking(acb_t c, config_t *config, calculated_point_t *calculated_point) {
    int i;
    acb_t f, z;

    acb_init(f);
    acb_init(z);

    // Period checking variables

    // Minimum number of iterations before using period checking.
    // It takes some iterations before the loop starts stabilising on the points.
    // TODO: what is the right number? is it a fix number?
    int min_iter_period_checking = 20;

    int check = 1;
    int check_counter = 0;

    int update = 10;
    int update_counter = 0;

    arb_t z_re, z_im;

    arb_t old_re, old_im;
    arb_t period_tolerance;

    // End period checking variables

    arb_init(z_re);
    arb_init(z_im);

    // Period checking initialization

    arb_init(old_re);
    arb_init(old_im);
    arb_init(period_tolerance);

    arb_set_str(old_re, "0.0", config->precision);
    arb_set_str(old_im, "0.0", config->precision);

    // TODO: this value should be calculated dynamically.
    // Gnofract 4D uses 0.00000001 at zoom 0 but with that value it does not detect a lot of periods.
    arb_set_str(period_tolerance, "0.01", config->precision);

    // End period checking initialization

    for (i = 1; i <= config->max_iterations; ++i) {

        calculated_point->iterations_taken = (unsigned int) i;

        mandelbrot_formula(f, z, c, config->precision);

        if (app_config_verbose_option_enabled(config, VO_PRINT_ITERATIONS)) {
            print_loop_iteration_with_periodicity_checking(
                    i,
                    check, check_counter, update, update_counter,
                    f, z, c,
                    z_re, z_im,
                    old_re, old_im,
                    period_tolerance
            );
        }

        if (bailout(f, config->precision)) {
            calculated_point->is_inside = FALSE;
            break;
        }

        acb_set(z, f);

        if (i >= min_iter_period_checking) {
            // Periodicity check

            // Get real and imaginary parts
            acb_get_real(z_re, z);
            acb_get_imag(z_im, z);

            // Check for period
            int period_found = check_for_period(i, c, z_re, z_im, old_re, old_im, period_tolerance, check_counter,
                                                config);

            if (period_found) {
                calculated_point->period = (unsigned int) check_counter;
                calculated_point->period_was_found = TRUE;
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

                if (app_config_verbose_option_enabled(config, VO_PRINT_PERIODS)) {
                    console_printf("->update old\n");
                }

                arb_set(old_re, z_re);
                arb_set(old_im, z_im);
            }
            // End of update history
            check_counter++;

            // End periodicity check
        }
    }

    arb_clear(z_re);
    arb_clear(z_im);
    arb_clear(old_re);
    arb_clear(old_im);

    arb_clear(period_tolerance);

    acb_clear(f);
    acb_clear(z);
}