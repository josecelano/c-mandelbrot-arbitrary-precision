#ifndef C_MANDELBROT_ARBITRARY_PRECISION_FRACTAL_DATA_H
#define C_MANDELBROT_ARBITRARY_PRECISION_FRACTAL_DATA_H

#include "./fractal.h"

typedef struct {
    resolution_t resolution;
    unsigned int number_of_found_periods;       // Number of periods found when it's used the periods checking optimisation.
    unsigned int max_for_number_of_iterations;  // Max number of iterations done of all points.
    calculated_point_t *calculated_points;      // Array of calculated points.
} fractal_data_t;

void fractal_matrix_init(fractal_data_t *fractal_data, resolution_t resolution);

void fractal_matrix_clean(fractal_data_t *fractal_data);

void fractal_matrix_initialize_iterations_taken(fractal_data_t *fractal_data, int *iterations_taken);

/**
 * Iteration taken matrix is flipped horizontally, that's is to say y pixel coordinates increase from bottom to top.
 * For standard graphics format (used in PPM format) (0,0) pixel coordinates is the left top corner of the image.
 */
int fractal_matrix_get_num_iter_per_point(fractal_data_t fractal_data, point_t point);

void fractal_matrix_set_calculated_point(fractal_data_t *fractal_data, point_t p, calculated_point_t calculated_point);

void fractal_matrix_get_calculated_point(fractal_data_t fractal_data, point_t p, calculated_point_t *calculated_point);

/**
 * For points inside Mandelbrot Set it returns MAX_ITERATIONS
 * For points outside it returns number of iterations needed to diverge.
 */
void fractal_matrix_calculate_points(ztile_t tile, config_t config, fractal_data_t *fractal_data);

#endif //C_MANDELBROT_ARBITRARY_PRECISION_FRACTAL_DATA_H
