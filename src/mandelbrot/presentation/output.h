#ifndef C_MANDELBROT_ARBITRARY_PRECISION_OUTPUT_H
#define C_MANDELBROT_ARBITRARY_PRECISION_OUTPUT_H

#include <time.h>

#include "../domain/fractal.h"

void print_loop_iteration(
        int i,
        int check, int check_counter, int update, int update_counter,
        acb_t f, acb_t z, acb_t c,
        arb_t z_re, arb_t z_im,
        arb_t old_re, arb_t old_im,
        arb_t period_tolerance
);

void print_period_checking(arb_t re_diff, arb_t im_diff);

void print_period_found(int period, int i);

void print_render_progress(int y, int height);

void print_performance_data(clock_t time, fractal_resolution resolution, app_config config);

#endif //C_MANDELBROT_ARBITRARY_PRECISION_OUTPUT_H
