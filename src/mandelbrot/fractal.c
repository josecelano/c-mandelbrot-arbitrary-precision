#include "acb.h"
#include "arb.h"
#include "complex.h"
#include "fractal.h"
#include "set.h"
#include "zpoint.h"
#include "ztile.h"

void calculate_matrix_point(
        zpoint z_current_point,
        int max_iterations,
        slong prec,
        int x, int y, int width,
        int *iterations_taken_matrix
) {
    int iterations_taken;

    // Check if point belongs to Mandelbrot Set
    iterations_taken = mandelbrot_set_contains(z_current_point, max_iterations, prec);

    // Update matrix with iterations counter for each point
    iterations_taken_matrix[(y * width) + x] = iterations_taken;
}

void calculate_matrix_row(
        zpoint zx_point_increment,
        int max_iterations,
        slong prec,
        int y, int width,
        // Output
        int *iterations_taken_matrix,
        zpoint *z_current_point
) {
    int x;

    for (x = 0; x < width; x++) {
        calculate_matrix_point(
                *z_current_point,
                max_iterations,
                prec,
                x, y, width,
                iterations_taken_matrix
        );

        // Increase real part to move one pixel to the right
        zpoint_add(z_current_point, *z_current_point, zx_point_increment, prec);
    }
}

void calculate_matrix(
        zpoint left_bottom_point,
        zpoint zx_point_increment,
        zpoint zy_point_increment,
        int max_iterations,
        slong prec,
        fractal_resolution resolution,
        // Output
        int *iterations_taken_matrix
) {
    int y;
    zpoint z_current_point; // Represents the pixel being calculated

    zpoint_init(&z_current_point);

    // Starting at left bottom corner of the image.
    zpoint_set(&z_current_point, &left_bottom_point);

    for (y = 0; y < resolution.height; y++) {

        calculate_matrix_row(
                zx_point_increment,
                max_iterations,
                prec,
                y, resolution.width,
                iterations_taken_matrix,
                &z_current_point
        );

        // Return back to first image column (pixel)
        zpoint_set_re(&z_current_point, left_bottom_point.re);

        // Increase imaginary part to move one pixel to the top
        zpoint_add(&z_current_point, z_current_point, zy_point_increment, prec);
    }

    zpoint_clean(&z_current_point);
}

void calculate_points(
        ztile tile, fractal_resolution resolution,
        int max_iterations,
        slong prec,
        int *iterations_taken_matrix
) {
    int x, y;
    int img_idx = 0;
    int iterations_taken;

    zpoint zx_point_increment, zy_point_increment;

    // Complex numbers
    acb_t point;

    // Real numbers
    arb_t zero;
    arb_t res_x_t, res_y_t;
    arb_t width, height;
    arb_t step_re, step_im;

    acb_init(point);

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
    // height step_im 4 / resolution.height
    // width step_re 4 / resolution.width
    // Each iter:
    // For width: previous re + step_re
    // For height: previous im + step_im

    // Convert resolution parameter to arb type in order to use them in arb operations
    arb_set_d(res_x_t, (double) resolution.width);
    arb_set_d(res_y_t, (double) resolution.height);

    // Calculate step between pixels
    arb_sub(width, tile.right_top_point.re, tile.left_bottom_point.re, prec);
    arb_sub(height, tile.right_top_point.im, tile.left_bottom_point.im, prec);

    arb_div(step_re, width, res_x_t, prec);
    arb_div(step_im, height, res_y_t, prec);

    zpoint_set_from_re_im(&zx_point_increment, step_re, zero);
    zpoint_set_from_re_im(&zy_point_increment, zero, step_im);

    // TODO: extraer el cálculo del incremento en x e y

    calculate_matrix(
            tile.left_bottom_point,
            zx_point_increment,
            zy_point_increment,
            max_iterations,
            prec,
            resolution,
            // Output
            iterations_taken_matrix
    );

    // Clean variables

    acb_clear(point);

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