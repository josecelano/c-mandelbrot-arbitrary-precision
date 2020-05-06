#include "acb.h"
#include "arb.h"
#include "complex.h"
#include "fractal.h"
#include "set.h"
#include "zpoint.h"

void calculate_points(int res_x, int res_y, int max_iterations, slong prec, int *iterations_taken_matrix) {
    int x, y;
    int img_idx = 0;
    int iterations_taken;

    zpoint left_bottom_point, right_top_point, z_current_point, zx_point_increment, zy_point_increment;

    // Complex numbers
    acb_t point;

    // Real numbers
    arb_t zero;
    arb_t res_x_t, res_y_t;
    arb_t width, height;
    arb_t step_re, step_im;

    acb_init(point);

    zpoint_init(&left_bottom_point);
    zpoint_init(&right_top_point);
    zpoint_init(&z_current_point);
    zpoint_init(&zx_point_increment);
    zpoint_init(&zy_point_increment);

    arb_init(zero);
    arb_init(res_x_t);
    arb_init(res_y_t);

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

    // Left bottom corner and right top corner complex number of the graph tile we are going to draw
    zpoint_set_from_re_im_str(&left_bottom_point, "-2", "-2", prec);
    zpoint_set_from_re_im_str(&right_top_point, "2", "2", prec);

    // Calculate step between pixels
    arb_sub(width, right_top_point.re, left_bottom_point.re, prec);
    arb_sub(height, right_top_point.im, left_bottom_point.im, prec);

    arb_div(step_re, width, res_x_t, prec);
    arb_div(step_im, height, res_y_t, prec);

    // Complex parts of complex representing the pixel being calculated.
    // Starting at left bottom corner of the image.
    zpoint_set(&z_current_point, &left_bottom_point);

    zpoint_set_from_re_im(&zx_point_increment, step_re, zero);
    zpoint_set_from_re_im(&zy_point_increment, zero, step_im);

    for (y = 0; y < res_y; y++) {
        for (x = 0; x < res_x; x++) {

            // Check if point belongs to Mandelbrot Set
            iterations_taken = mandelbrot_set_contains(z_current_point, max_iterations, prec);

            // Update matrix with iterations counter for each point
            iterations_taken_matrix[(y * res_x) + x] = iterations_taken;

            // Increase real part to move one pixel to the right
            zpoint_add(&z_current_point, z_current_point, zx_point_increment, prec);
        }

        // Return back to first image column (pixel)
        zpoint_set_re(&z_current_point, left_bottom_point.re);

        // Increase imaginary part to move one pixel to the top
        zpoint_add(&z_current_point, z_current_point, zy_point_increment, prec);
    }

    // Clean variables

    acb_clear(point);

    zpoint_clean(&left_bottom_point);
    zpoint_clean(&right_top_point);
    zpoint_clean(&z_current_point);
    zpoint_clean(&zx_point_increment);
    zpoint_clean(&zy_point_increment);

    arb_clear(zero);
    arb_clear(res_x_t);
    arb_clear(res_y_t);

    arb_clear(width);
    arb_clear(height);

    arb_clear(step_re);
    arb_clear(step_im);
}