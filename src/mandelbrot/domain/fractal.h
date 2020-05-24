#ifndef C_MANDELBROT_ARBITRARY_PRECISION_FRACTAL_H
#define C_MANDELBROT_ARBITRARY_PRECISION_FRACTAL_H

#include "acb.h"
#include "ztile.h"

#include "../application/config.h"
#include "point.h"

typedef struct {
    int width;
    int height;
} fractal_resolution;

typedef enum {
    TRUE = 1,
    FALSE = 0
} fractal_boolean;

typedef struct {
    fractal_boolean is_inside;          // Point inside/outside Mandelbrot Set.
    unsigned int iterations_taken;      // Number of iterations done in the main fractal processing loop.
    fractal_boolean period_was_found;   // True if period was found.
    unsigned int period;                // if a period is found in the loop this will contain the period cycle length otherwise 0.
} fractal_calculated_point;

/**
 * Matrix[width][height] with number of Mandelbrot formula iterations needed for each pixel to diverge.
 * -1 for point/pixel inside Mandelbrot Set.
 */
typedef struct {
    fractal_resolution resolution;
    unsigned int number_of_found_periods;   // Number of periods found when it's used the periods checking optimisation.
    int *data;
} fractal_matrix;

void fractal_calculated_point_init(fractal_calculated_point *calculated_point);

void fractal_calculated_point_set_in_main_cardioid(fractal_calculated_point *calculated_point);

void fractal_calculated_point_set_in_period2_bulb(fractal_calculated_point *calculated_point);

void fractal_matrix_init(fractal_matrix *iterations_taken_matrix, fractal_resolution resolution);

void fractal_matrix_clean(fractal_matrix *iterations_taken_matrix);

void fractal_matrix_initialize_data(fractal_matrix iterations_taken_matrix, int *iterations_taken);

/**
 * Iteration taken matrix is flipped horizontally, that's is to say y pixel coordinates increase from bottom to top.
 * For standard graphics format (used in PPM format) (0,0) pixel coordinates is the left top corner of the image.
 */
int fractal_matrix_get_num_iter_per_point(point p, fractal_matrix iterations_taken_matrix);

/**
 * It returns INSIDE if the point in the matrix belongs to Mandelbrot Set.
 */
int fractal_matrix_point_belongs_to_mandelbrot_set(point p, fractal_matrix iterations_taken_matrix);

/**
 * For points inside Mandelbrot Set it returns MAX_ITERATIONS
 * For points outside it returns number of iterations needed to diverge.
 */
void fractal_matrix_calculate_points(ztile tile, app_config config, fractal_matrix *iterations_taken_matrix);

#endif //C_MANDELBROT_ARBITRARY_PRECISION_FRACTAL_H