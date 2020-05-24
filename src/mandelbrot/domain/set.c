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

int mandelbrot_set_contains(zpoint point, app_config config) {
    fractal_calculated_point calculated_point;

    fractal_calculated_point_init(&calculated_point);

    mandelbrot_set_calculate_point(point, config, &calculated_point);

    return calculated_point.is_inside ? INSIDE : OUTSIDE;
}

int is_value_a_inside_point(int num_iter_for_pixel) {
    if (num_iter_for_pixel == MAX_ITERATIONS) {
        return INSIDE;
    }

    return OUTSIDE;
}

void mandelbrot_set_calculate_point(zpoint point, app_config config, fractal_calculated_point *calculated_point) {
    acb_t c;

    acb_init(c);

    acb_set_from_zpoint(c, point);

    if (inside_main_cardioid(c, config)) {
        fractal_calculated_point_set_in_main_cardioid(calculated_point);
        acb_clear(c);
        return;
    }

    if (inside_period_2_bulb(c, config)) {
        fractal_calculated_point_set_in_period2_bulb(calculated_point);
        acb_clear(c);
        return;
    }

    execute_iterations_with_period_checking(c, config, calculated_point);

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