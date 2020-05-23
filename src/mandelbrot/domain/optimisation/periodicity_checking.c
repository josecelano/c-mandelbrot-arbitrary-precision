#include "periodicity_checking.h"

int check_for_period(int iter, acb_t c, arb_t z_re, arb_t z_im, arb_t old_re, arb_t old_im, arb_t period_tolerance,
                     int check_counter, app_config config) {
    int ret = 0;

    arb_t re_diff, im_diff;

    arb_init(re_diff);
    arb_init(im_diff);

    // re_diff = abs(re - h_re)
    arb_sub(re_diff, z_re, old_re, config.precision);
    arb_abs(re_diff, re_diff);

    // im_diff = abs(im - h_im)
    arb_sub(im_diff, z_im, old_im, config.precision);
    arb_abs(im_diff, im_diff);

    if (app_config_verbose_option_enabled(config, PRINT_PERIODS)) {
        print_period_checking(re_diff, im_diff);
    }

    if (arb_lt(re_diff, period_tolerance) && arb_lt(im_diff, period_tolerance)) {
        // Period found
        if (app_config_verbose_option_enabled(config, PRINT_PERIODS)) {
            print_period_found(check_counter, iter);
        }
        ret = 1;
    }

    arb_clear(re_diff);
    arb_clear(im_diff);

    return ret;
}