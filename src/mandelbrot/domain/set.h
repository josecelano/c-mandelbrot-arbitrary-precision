#ifndef C_MANDELBROT_ARBITRARY_PRECISION_SET_H
#define C_MANDELBROT_ARBITRARY_PRECISION_SET_H

#include "acb.h"

#include "../application/config.h"
#include "./optimisation/main_cardioid_detection.h"
#include "./zpoint.h"

#define MAX_ITERATIONS  -1
#define INSIDE  1
#define OUTSIDE  0

/**
 * It returns INSIDE if the point belongs to mandelbrot Set and OUTSIDE if it does not.
 */
int mandelbrot_set_contains(zpoint point, int max_iterations, app_config config);

/**
 * Check is the value in the matrix represents a point inside the Mandelbrot Set.
 */
int is_value_a_inside_point(int num_iter_for_pixel);

/**
 * Bailout formula:
 * Zx²+Zy² < ER²
 * It returns 1 if we have reached the escape condition. The points diverges (does not belong to set).
 * https://en.wikibooks.org/wiki/Fractals/Iterations_in_the_complex_plane/Mandelbrot_set/mandelbrot#Bailout_test
 */
int bailout(acb_t c, slong prec);

/**
 * Same output values as execute_iterations_with_period_checking
 */
void
mandelbrot_set_calculate_point(zpoint point, int max_iterations, app_config config, int *inside, int *iterations_taken,
                               int *period);

/**
 * For:
 * Complex inside the Mandelbrot Set  -> returns
 *      * inside = 1
 *      * num_iter = number of iterations executed
 *      * period = if period was detected -> the period cycle length otherwise 0.
 * Complex outside the Mandelbrot Set -> returns
 *      * inside = 0
 *      * num_iter = the maximum number of iterations.
 *      * period = 0
 */
void execute_iterations_with_period_checking(acb_t c, int max_iterations, app_config config, int *inside,
                                             int *iterations_taken, int *period);

#endif //C_MANDELBROT_ARBITRARY_PRECISION_SET_H