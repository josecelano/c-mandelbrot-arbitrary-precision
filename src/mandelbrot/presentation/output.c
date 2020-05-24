#include "acb.h"
#include "arb.h"
#include <time.h>

#include "../domain/fractal.h"
#include "../infrastructure/console.h"

void print_loop_iteration(
        int i,
        int check, int check_counter, int update, int update_counter,
        acb_t f, acb_t z, acb_t c,
        arb_t z_re, arb_t z_im,
        arb_t old_re, arb_t old_im,
        arb_t period_tolerance
) {
    console_printf("\niter %d\n", i);
    console_printf("check %d check_counter %d update %d update_counter %d\n", check, check_counter, update, update_counter);
    console_print_complex("f       = ", f);
    console_print_complex("z       = ", z);
    console_print_complex("c       = ", c);
    console_print_real("z_re    = ", z_re);
    console_print_real("z_im    = ", z_im);
    console_print_real("old_re  = ", old_re);
    console_print_real("old_im  = ", old_im);
    console_print_real("tolerance = ", period_tolerance);
}

void print_period_checking(arb_t re_diff, arb_t im_diff) {
    console_print_real("re_diff   = ", re_diff);
    console_print_real("im_diff   = ", im_diff);
}

void print_period_found(int period, int i) {
    console_printf("Period %d found in iter %d!\n", period, i);
}

void print_render_progress(int y, int height) {
    // Delete current line
    console_printf("%c[2K\r", 27);

    // Print progress
    console_printf("Progress: %f%%", (double) y / height * 100);

    console_flush();
}

void print_performance_data(clock_t time, fractal_resolution resolution, app_config config) {
    int number_of_pixels = resolution.width * resolution.height;
    double time_taken_in_seconds = ((double) time) / CLOCKS_PER_SEC;
    long double time_taken_in_nanoseconds = time_taken_in_seconds * 1000000000;

    console_printf("\nFor %dx%dpx image:\n", resolution.width, resolution.height);
    console_printf("* Size: %dx%dpx (%d)\n", resolution.width, resolution.height, number_of_pixels);
    console_printf("* Max iter: %d\n", config.max_iterations);
    console_printf("* Precision: %ld\n", config.precision);
    console_printf("* Time for matrix generation: %fs = %Lfns\n", time_taken_in_seconds, time_taken_in_nanoseconds);
    console_printf("* Performance: %Le‬ ns/px\n",
           ((long double) time_taken_in_seconds / number_of_pixels) * 1000000000); // In nanoseconds
    console_printf("* Minimum complex x increment: %Le (4/%d)\n", (long double) 4 / resolution.width, resolution.width);
    console_printf("* Minimum complex y increment: %Le (4/%d)\n", (long double) 4 / resolution.height, resolution.height);
}

void print_fractal_matrix_data(fractal_matrix matrix) {
    console_printf("* Number of found periods: %d\n", matrix.number_of_found_periods);
    console_printf("* Max for number of iterations: %d (should be max iterations in config)\n", matrix.max_for_number_of_iterations);
}