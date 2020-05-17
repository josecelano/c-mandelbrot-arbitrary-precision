#ifndef C_MANDELBROT_ARBITRARY_PRECISION_OUTPUT_H
#define C_MANDELBROT_ARBITRARY_PRECISION_OUTPUT_H

#include <time.h>

#include "../domain/fractal.h"

void print_period(
        int i,
        acb_t c,
        arb_t z_re, arb_t z_im,
        arb_t old_re, arb_t old_im,
        arb_t re_diff, arb_t im_diff
);

void print_render_progress(int y, int height);

void print_performance_data(
        clock_t time,
        fractal_resolution resolution,
        int max_iterations,
        slong prec
);

#endif //C_MANDELBROT_ARBITRARY_PRECISION_OUTPUT_H
