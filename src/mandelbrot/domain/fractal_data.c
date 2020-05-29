#include "../presentation/output.h"
#include "./calculated_point.h"
#include "./fractal_data.h"
#include "./set.h"

/** Private functions **/

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

void calculate_matrix_point(
        zpoint_t z_current_point,
        point_t pt,
        config_t *config,
        fractal_data_t *fractal_data
) {
    calculated_point_t calculated_point;

    fractal_calculated_point_init(&calculated_point);

    mandelbrot_set_calculate_point(z_current_point, config, &calculated_point);

    fractal_data_set_calculated_point(fractal_data, pt, calculated_point);
}

void calculate_next_point_to_the_right(zpoint_t *z, zpoint_t z_current_point, zpoint_t zx_point_increment, slong prec) {
    // Increase real part to move one pixel to the right
    zpoint_add(z, z_current_point, zx_point_increment, prec);
}

void calculate_matrix_row(
        zpoint_t zx_point_increment,
        config_t *config,
        int y,
        fractal_data_t *fractal_data,
        zpoint_t *z_current_point
) {
    int x;
    int width = fractal_data->resolution.width;
    point_t current_point;

    for (x = 0; x < width; x++) {
        point_set_coordinates(&current_point, x, y);

        calculate_matrix_point(
                *z_current_point, current_point,
                config,
                fractal_data);

        calculate_next_point_to_the_right(z_current_point, *z_current_point, zx_point_increment, config->precision);
    }
}

void calculate_points(
        zpoint_t left_bottom_point,
        zpoint_t zx_point_increment, zpoint_t zy_point_increment,
        config_t *config, fractal_data_t *fractal_data
) {
    int y;
    zpoint_t z_current_point; // Represents the pixel being calculated
    resolution_t resolution = fractal_data->resolution;

    zpoint_init(&z_current_point);

    // Starting at left bottom corner of the image.
    zpoint_set(&z_current_point, &left_bottom_point);

    for (y = 0; y < resolution.height; y++) {

        calculate_matrix_row(
                zx_point_increment,
                config,
                y,
                fractal_data,
                &z_current_point
        );

        if (app_config_verbose_option_enabled(config, VO_PRINT_PROGRESS)) {
            print_render_progress(y, resolution.height);
        }

        // Return back to first image column (pixel)
        zpoint_set_re(&z_current_point, left_bottom_point.re);

        // Increase imaginary part to move one pixel to the top
        zpoint_add(&z_current_point, z_current_point, zy_point_increment, config->precision);
    }

    zpoint_clean(&z_current_point);
}

/** Public functions **/

void fractal_data_init(fractal_data_t *fractal_data, resolution_t resolution) {
    int matrix_size;

    // Resolution
    fractal_data->resolution.width = resolution.width;
    fractal_data->resolution.height = resolution.height;

    // Aggregated data
    fractal_data->number_of_found_periods = 0;
    fractal_data->max_for_number_of_iterations = 0;

    // Calculated points matrix
    matrix_size = resolution.width * resolution.height * sizeof(calculated_point_t);
    fractal_data->calculated_points = malloc(matrix_size);
    if (fractal_data->calculated_points == NULL) {
        printf("Exception (fractal_data init). Unable to allocate memory.\n");
        abort();
    }

    // TODO: Code Review, Should we initialize the calculated_points matrix with a state?
    // Maybe a new member in calculated_point.is_calculated?
}

void fractal_data_clean(fractal_data_t *fractal_data) {
    free(fractal_data->calculated_points);
}

void fractal_data_set_calculated_point(fractal_data_t *fractal_data, point_t point, calculated_point_t calculated_point) {
    // Store calculated point in the matrix struct member
    fractal_data->calculated_points[(point.y * fractal_data->resolution.width) + point.x] = calculated_point;

    // Update periods counter
    if (calculated_point.period_was_found) {
        fractal_data->number_of_found_periods++;
    }

    // Update maximum for number of iterations
    if (calculated_point.iterations_taken > fractal_data->max_for_number_of_iterations) {
        fractal_data->max_for_number_of_iterations = calculated_point.iterations_taken;
    }
}

void fractal_data_get_calculated_point(fractal_data_t fractal_data, point_t point, calculated_point_t *calculated_point) {
    *calculated_point = fractal_data.calculated_points[(point.y * fractal_data.resolution.width) + point.x];
}

void fractal_data_calculate_points(fractal_data_t *fractal_data, ztile_t tile, config_t *config) {
    zpoint_t zx_point_increment, zy_point_increment;

    zpoint_init(&zx_point_increment);
    zpoint_init(&zy_point_increment);

    calculate_real_and_imaginary_increments_per_point(
            tile,
            fractal_data->resolution,
            config->precision,
            // Output
            &zx_point_increment,
            &zy_point_increment
    );

    calculate_points(
            tile.left_bottom_point,
            zx_point_increment,
            zy_point_increment,
            config,
            // Output
            fractal_data
    );

    zpoint_clean(&zx_point_increment);
    zpoint_clean(&zy_point_increment);
}