#include "acb.h"
#include "arb.h"
#include <time.h>

#include "../domain/fractal.h"
#include "../infrastructure/console.h"

void print_period(
        int i,
        acb_t c,
        arb_t z_re, arb_t z_im,
        arb_t old_re, arb_t old_im,
        arb_t re_diff, arb_t im_diff
) {
    console_printf("\nPeriod found:\n");
    console_printf("iter    = %d\n", i);
    console_print_complex("c       = ", c);
    console_print_real("z_re    = ", z_re);
    console_print_real("z_im    = ", z_im);
    console_print_real("old_re  = ", old_re);
    console_print_real("old_im  = ", old_im);
    console_print_real("re_diff = ", re_diff);
    console_print_real("im_diff = ", im_diff);
}

void print_render_progress(int y, int height) {
    // Delete current line
    console_printf("%c[2K\r", 27);

    // Print progress
    console_printf("Progress: %f%%", (double) y / height * 100);

    console_flush();
}

void print_performance_data(
        clock_t time,
        fractal_resolution resolution,
        int max_iterations,
        slong prec
) {
    int number_of_pixels = resolution.width * resolution.height;
    double time_taken_in_seconds = ((double) time) / CLOCKS_PER_SEC;
    long double time_taken_in_nanoseconds = time_taken_in_seconds * 1000000000;

    console_printf("\nFor %dx%dpx image:\n", resolution.width, resolution.height);
    console_printf("* Size: %dx%dpx (%d)\n", resolution.width, resolution.height, number_of_pixels);
    console_printf("* Max iter: %d\n", max_iterations);
    console_printf("* Precision: %ld\n", prec);
    console_printf("* Time for matrix generation: %fs = %Lfns\n", time_taken_in_seconds, time_taken_in_nanoseconds);
    console_printf("* Performance: %Le‬ ns/px\n",
           ((long double) time_taken_in_seconds / number_of_pixels) * 1000000000); // In nanoseconds
    console_printf("* Minimum complex x increment: %Le (4/%d)\n", (long double) 4 / resolution.width, resolution.width);
    console_printf("* Minimum complex y increment: %Le (4/%d)\n", (long double) 4 / resolution.height, resolution.height);
}