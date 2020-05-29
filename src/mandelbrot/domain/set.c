#include "acb.h"
#include "arb.h"

#include "../infrastructure/console.h"
#include "../presentation/output.h"
#include "./calculated_point.h"
#include "./complex.h"
#include "./formula.h"
#include "./optimisation/main_cardioid_detection.h"
#include "./optimisation/period2_detection.h"
#include "./optimisation/periodicity_checking.h"
#include "./set.h"
#include "./zpoint.h"

int mandelbrot_set_contains(zpoint_t point, config_t *config) {
    calculated_point_t calculated_point;

    fractal_calculated_point_init(&calculated_point);

    mandelbrot_set_calculate_point(point, config, &calculated_point);

    return calculated_point.is_inside ? INSIDE : OUTSIDE;
}

void execute_iterations(acb_t c, config_t *config, calculated_point_t *calculated_point) {
    int i;
    acb_t f, z;

    acb_init(f);
    acb_init(z);

    arb_t z_re, z_im;

    arb_init(z_re);
    arb_init(z_im);

    for (i = 1; i <= config->max_iterations; ++i) {

        calculated_point->iterations_taken = (unsigned int) i;

        mandelbrot_formula(f, z, c, config->precision);

        if (app_config_verbose_option_enabled(config, VO_PRINT_ITERATIONS)) {
            print_loop_iteration(i, f, z, c, z_re, z_im);
        }

        if (bailout(f, config->precision)) {
            calculated_point->is_inside = FALSE;
            break;
        }

        acb_set(z, f);
    }

    arb_clear(z_re);
    arb_clear(z_im);

    acb_clear(f);
    acb_clear(z);
}

void mandelbrot_set_calculate_point(zpoint_t point, config_t *config, calculated_point_t *calculated_point) {
    acb_t c;

    acb_init(c);

    acb_set_from_zpoint(c, point);

    if (app_config_optimisation_option_enabled(config, OO_MAIN_CARDIOID_DETECTION)) {
        if (inside_main_cardioid(c, config)) {
            fractal_calculated_point_set_in_main_cardioid(calculated_point);
            acb_clear(c);
            return;
        }
    }

    if (app_config_optimisation_option_enabled(config, OO_PERIOD2_DETECTION)) {
        if (inside_period_2_bulb(c, config)) {
            fractal_calculated_point_set_in_period2_bulb(calculated_point);
            acb_clear(c);
            return;
        }
    }

    if (app_config_optimisation_option_enabled(config, OO_PERIODICITY_CHECKING)) {
        execute_iterations_with_period_checking(c, config, calculated_point);
        acb_clear(c);
        return;
    }

    execute_iterations(c, config, calculated_point);

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