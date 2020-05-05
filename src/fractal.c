#include "acb.h"
#include "arb.h"
#include "complex.h"
#include "fractal.h"
#include "set.h"

void calculate_points(int res_x, int res_y, int max_iterations, slong prec, int *iterations_taken_matrix) {
    int x, y;
    int img_idx = 0;
    int iterations_taken;

    // Complex numbers
    acb_t point;

    // Real numbers
    arb_t res_x_t, res_y_t;
    arb_t lb_re, lb_im;
    arb_t rt_re, rt_im;
    arb_t pixel_re, pixel_im;
    arb_t width, height;
    arb_t step_re, step_im;

    acb_init(point);

    arb_init(res_x_t);
    arb_init(res_y_t);

    arb_init(lb_re);
    arb_init(lb_im);

    arb_init(rt_re);
    arb_init(rt_im);

    arb_init(pixel_re);
    arb_init(pixel_im);

    arb_init(width);
    arb_init(height);

    arb_init(step_re);
    arb_init(step_im);

    // Image is rendered from left bottom corner to right top corner
    // Fix tile size.
    // Initial complex point -2,-2
    // Final complex point 2, 2
    // height step_im 4 / res_y
    // width step_re 4 / res_x
    // Each iter:
    // For width: previous re + step_re
    // For height: previous im + step_im

    // Convert resolution parameter to arb type in order to use them in arb operations
    arb_set_d(res_x_t, (double) res_x);
    arb_set_d(res_y_t, (double) res_y);

    // Left bottom corner complex
    arb_set_str(lb_re, "-2", prec);
    arb_set_str(lb_im, "-2", prec);

    // Right top corner complex
    arb_set_str(rt_re, "2", prec);
    arb_set_str(rt_im, "2", prec);

    // Calculate step between pixels
    arb_sub(width, rt_re, lb_re, prec);
    arb_sub(height, rt_im, lb_im, prec);
    arb_div(step_re, width, res_x_t, prec);
    arb_div(step_im, height, res_y_t, prec);

    // Complex parts of complex representing the pixel being calculated (pixel_re, pixel_im).
    // Starting at left bottom corner of the image.
    arb_set(pixel_re, lb_re);
    arb_set(pixel_im, lb_im);

    for (y = 0; y < res_y; y++) {
        for (x = 0; x < res_x; x++) {

            // Calculate complex point
            complex_set_from_re_im(point, pixel_re, pixel_im);

            // Check if point belongs to Mandelbrot Set
            iterations_taken = mandelbrot_set_contains(point, max_iterations, prec);

            iterations_taken_matrix[(y * res_x) + x] = iterations_taken;

            // Increase real part to move one pixel to the right
            arb_add(pixel_re, pixel_re, step_re, prec);
        }

        // Return back to first image column (pixel)
        arb_set(pixel_re, lb_re);

        // Increase imaginary part to move one pixel to the top
        arb_add(pixel_im, pixel_im, step_im, prec);
    }

    // Clean variables

    acb_clear(point);

    arb_clear(res_x_t);
    arb_clear(res_y_t);

    arb_clear(lb_re);
    arb_clear(lb_im);

    arb_clear(rt_re);
    arb_clear(rt_im);

    arb_clear(pixel_re);
    arb_clear(pixel_im);

    arb_clear(width);
    arb_clear(height);

    arb_clear(step_re);
    arb_clear(step_im);
}