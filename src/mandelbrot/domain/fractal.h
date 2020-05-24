#ifndef C_MANDELBROT_ARBITRARY_PRECISION_FRACTAL_H
#define C_MANDELBROT_ARBITRARY_PRECISION_FRACTAL_H

#include "acb.h"
#include "ztile.h"

#include "../application/config.h"
#include "point.h"

typedef struct {
    int width;
    int height;
} resolution_t;

typedef enum {
    TRUE = 1,
    FALSE = 0
} boolean_t;

typedef struct {
    boolean_t is_inside;          // Point inside/outside Mandelbrot Set.
    unsigned int iterations_taken;      // Number of iterations done in the main fractal processing loop.
    boolean_t period_was_found;   // True if period was found.
    unsigned int period;                // if a period is found in the loop this will contain the period cycle length otherwise 0.
} calculated_point_t;

/**
 * Matrix[width][height] with number of Mandelbrot formula iterations needed for each pixel to diverge.
 * -1 for point/pixel inside Mandelbrot Set.
 */
typedef struct {
    resolution_t resolution;
    unsigned int number_of_found_periods;   // Number of periods found when it's used the periods checking optimisation.
    unsigned int max_for_number_of_iterations;  // Max number of iterations done of all points.
    int *data;
} matrix_t;

void fractal_calculated_point_init(calculated_point_t *calculated_point);

void fractal_calculated_point_set_in_main_cardioid(calculated_point_t *calculated_point);

void fractal_calculated_point_set_in_period2_bulb(calculated_point_t *calculated_point);

void fractal_matrix_init(matrix_t *iterations_taken_matrix, resolution_t resolution);

void fractal_matrix_clean(matrix_t *iterations_taken_matrix);

void fractal_matrix_initialize_data(matrix_t iterations_taken_matrix, int *iterations_taken);

/**
 * Iteration taken matrix is flipped horizontally, that's is to say y pixel coordinates increase from bottom to top.
 * For standard graphics format (used in PPM format) (0,0) pixel coordinates is the left top corner of the image.
 */
int fractal_matrix_get_num_iter_per_point(point_t p, matrix_t iterations_taken_matrix);

/**
 * It returns INSIDE if the point in the matrix belongs to Mandelbrot Set.
 */
int fractal_matrix_point_belongs_to_mandelbrot_set(point_t p, matrix_t iterations_taken_matrix);

/**
 * For points inside Mandelbrot Set it returns MAX_ITERATIONS
 * For points outside it returns number of iterations needed to diverge.
 */
void fractal_matrix_calculate_points(ztile_t tile, config_t config, matrix_t *iterations_taken_matrix);

#endif //C_MANDELBROT_ARBITRARY_PRECISION_FRACTAL_H