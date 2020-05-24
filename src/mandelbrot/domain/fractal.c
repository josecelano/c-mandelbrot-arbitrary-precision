#include <string.h>
#include <stdio.h>

#include "acb.h"
#include "arb.h"

#include "../presentation/output.h"
#include "./complex.h"
#include "./fractal.h"
#include "./optimisation/main_cardioid_detection.h"
#include "./optimisation/period2_detection.h"
#include "./optimisation/periodicity_checking.h"
#include "./set.h"
#include "./zpoint.h"
#include "./ztile.h"

void fractal_calculated_point_init(calculated_point_t *calculated_point) {
    calculated_point->is_inside = TRUE;
    calculated_point->iterations_taken = 0;
    calculated_point->period_was_found = FALSE;
    calculated_point->period = 0;
}

void fractal_calculated_point_set_in_main_cardioid(calculated_point_t *calculated_point) {
    calculated_point->is_inside = TRUE;
    calculated_point->iterations_taken = 0;
    calculated_point->period_was_found = TRUE;
    calculated_point->period = 1;
}

void fractal_calculated_point_set_in_period2_bulb(calculated_point_t *calculated_point) {
    calculated_point->is_inside = TRUE;
    calculated_point->iterations_taken = 0;
    calculated_point->period_was_found = TRUE;
    calculated_point->period = 2;
}

void fractal_matrix_init(matrix_t *iterations_taken_matrix, resolution_t resolution) {
    int matrix_size;

    // Resolution
    iterations_taken_matrix->resolution.width = resolution.width;
    iterations_taken_matrix->resolution.height = resolution.height;

    iterations_taken_matrix->number_of_found_periods = 0;
    iterations_taken_matrix->max_for_number_of_iterations = 0;

    // Matrix
    matrix_size = resolution.width * resolution.height * sizeof(int);
    iterations_taken_matrix->data = malloc(matrix_size);
}

void fractal_matrix_clean(matrix_t *iterations_taken_matrix) {
    free(iterations_taken_matrix->data);
}

void fractal_matrix_set_num_iter_per_point(matrix_t *iterations_taken_matrix, point_t p, int iterations_taken) {
    iterations_taken_matrix->data[(p.y * iterations_taken_matrix->resolution.width) + p.x] = iterations_taken;
}

/*
 * TODO: WIP refactor
 * fractal_matrix.data stores -1 for points inside Mandelbrot Set.
 * -1 means max number of iterations in the loop.
 * Matrix should contain the real number of iterations and an additional value that indicates whether the point
 * is inside or not. The matrix should contain "fractal_calculated_point" instead of "int".
 */
void fractal_matrix_set_calculated_point(matrix_t *iterations_taken_matrix, point_t p,
                                         calculated_point_t calculated_point) {
    int iterations_taken;

    iterations_taken = calculated_point.iterations_taken;

    // TODO: remove when refactor is done
    if (calculated_point.is_inside) {
        iterations_taken = MAX_ITERATIONS;
    }

    fractal_matrix_set_num_iter_per_point(iterations_taken_matrix, p, iterations_taken);

    // Update periods counter
    if (calculated_point.period_was_found) {
        iterations_taken_matrix->number_of_found_periods++;
    }

    // Update maximum for number of iterations
    if (calculated_point.iterations_taken > iterations_taken_matrix->max_for_number_of_iterations) {
        iterations_taken_matrix->max_for_number_of_iterations = calculated_point.iterations_taken;
    }
}

void fractal_matrix_initialize_data(matrix_t iterations_taken_matrix, int *iterations_taken) {
    int i;
    int size = iterations_taken_matrix.resolution.width * iterations_taken_matrix.resolution.height;

    for (i = 0; i < size; i++) {
        iterations_taken_matrix.data[i] = iterations_taken[i];
    }
}

int fractal_matrix_get_num_iter_per_point(point_t p, matrix_t iterations_taken_matrix) {
    int width = iterations_taken_matrix.resolution.width;
    int height = iterations_taken_matrix.resolution.height;

    return iterations_taken_matrix.data[(height - 1 - p.y) * width + p.x];
}

int fractal_matrix_point_belongs_to_mandelbrot_set(point_t p, matrix_t iterations_taken_matrix) {
    int num_iter_for_pixel = fractal_matrix_get_num_iter_per_point(p, iterations_taken_matrix);
    return is_value_a_inside_point(num_iter_for_pixel);
}

void
calculate_matrix_point(zpoint_t z_current_point, point_t pt, config_t config, matrix_t *iterations_taken_matrix) {
    calculated_point_t calculated_point;
    fractal_calculated_point_init(&calculated_point);

    mandelbrot_set_calculate_point(z_current_point, config, &calculated_point);

    fractal_matrix_set_calculated_point(iterations_taken_matrix, pt, calculated_point);
}

void calculate_next_point_to_the_right(zpoint_t *z, zpoint_t z_current_point, zpoint_t zx_point_increment, slong prec) {
    // Increase real part to move one pixel to the right
    zpoint_add(z, z_current_point, zx_point_increment, prec);
}

void calculate_matrix_row(zpoint_t zx_point_increment, config_t config, int y, matrix_t *iterations_taken_matrix,
                          zpoint_t *z_current_point) {
    int x;
    int width = iterations_taken_matrix->resolution.width;
    point_t current_point;

    for (x = 0; x < width; x++) {
        point_set(&current_point, x, y);

        calculate_matrix_point(
                *z_current_point, current_point,
                config,
                iterations_taken_matrix);

        calculate_next_point_to_the_right(z_current_point, *z_current_point, zx_point_increment, config.precision);
    }
}

void calculate_iterations_taken_matrix(zpoint_t left_bottom_point, zpoint_t zx_point_increment, zpoint_t zy_point_increment,
                                       config_t config, matrix_t *iterations_taken_matrix) {
    int y;
    zpoint_t z_current_point; // Represents the pixel being calculated
    resolution_t resolution = iterations_taken_matrix->resolution;

    zpoint_init(&z_current_point);

    // Starting at left bottom corner of the image.
    zpoint_set(&z_current_point, &left_bottom_point);

    for (y = 0; y < resolution.height; y++) {

        calculate_matrix_row(
                zx_point_increment,
                config,
                y,
                iterations_taken_matrix,
                &z_current_point
        );

        if (app_config_verbose_option_enabled(config, PRINT_PROGRESS)) {
            print_render_progress(y, resolution.height);
        }

        // Return back to first image column (pixel)
        zpoint_set_re(&z_current_point, left_bottom_point.re);

        // Increase imaginary part to move one pixel to the top
        zpoint_add(&z_current_point, z_current_point, zy_point_increment, config.precision);
    }

    zpoint_clean(&z_current_point);
}

void calculate_real_and_imaginary_increments_per_point(
        ztile_t tile,
        resolution_t resolution,
        slong prec,
        // Output
        zpoint_t *zx_point_increment,
        zpoint_t *zy_point_increment
) {
    arb_t zero;
    arb_t res_x_t, res_y_t;
    arb_t width, height;
    arb_t step_re, step_im;

    arb_init(zero);

    arb_init(res_x_t);
    arb_init(res_y_t);

    arb_init(width);
    arb_init(height);

    arb_init(step_re);
    arb_init(step_im);

    // Image is rendered from left bottom corner to right top corner
    // Assuming completed Mandelbrot set tile:
    // height step_im 4 / resolution.height
    // width step_re 4 / resolution.width
    // Each iteration we calculate the complex number for the pixel/point increasing the current one parts (re,im):
    // For width: previous re + step_re
    // For height: previous im + step_im

    // Convert resolution parameter to arb type in order to use them in arb operations
    arb_set_d(res_x_t, (double) resolution.width);
    arb_set_d(res_y_t, (double) resolution.height);

    // Calculate width and height of the fractal to draw in real numbers
    arb_sub(width, tile.right_top_point.re, tile.left_bottom_point.re, prec);
    arb_sub(height, tile.right_top_point.im, tile.left_bottom_point.im, prec);

    // Calculate step/delta/increment between pixels/points
    arb_div(step_re, width, res_x_t, prec);
    arb_div(step_im, height, res_y_t, prec);

    zpoint_set_from_re_im(zx_point_increment, step_re, zero);
    zpoint_set_from_re_im(zy_point_increment, zero, step_im);

    arb_clear(zero);

    arb_clear(res_x_t);
    arb_clear(res_y_t);

    arb_clear(width);
    arb_clear(height);

    arb_clear(step_re);
    arb_clear(step_im);
}

void fractal_matrix_calculate_points(ztile_t tile, config_t config, matrix_t *iterations_taken_matrix) {
    int x, y;
    int img_idx = 0;
    int iterations_taken;

    zpoint_t zx_point_increment, zy_point_increment;

    zpoint_init(&zx_point_increment);
    zpoint_init(&zy_point_increment);

    calculate_real_and_imaginary_increments_per_point(
            tile,
            iterations_taken_matrix->resolution,
            config.precision,
            // Output
            &zx_point_increment,
            &zy_point_increment
    );

    calculate_iterations_taken_matrix(
            tile.left_bottom_point,
            zx_point_increment,
            zy_point_increment,
            config,
            // Output
            iterations_taken_matrix
    );

    zpoint_clean(&zx_point_increment);
    zpoint_clean(&zy_point_increment);
}