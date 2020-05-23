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
int mandelbrot_set_contains(zpoint point, int max_iterations, slong prec, app_config config);

/**
 * Check is the value in the matrix represents a point inside the Mandelbrot Set.
 */
int is_value_a_inside_point(int num_iter_for_pixel);

/**
 * It returns the number of iterations recursively applied to the basic Mandelbrot formula z²+c until the value diverges.
 * If MAX_ITERATIONS is reached it returns MAX_ITERATIONS, which means the point is inside the Mandelbrot Set.
 */
int mandelbrot_set_calculate_num_iterations_for(zpoint point, int max_iterations, slong prec, app_config config);

/**
 * Bailout formula:
 * Zx²+Zy² < ER²
 * It returns 1 if we have reached the escape condition. The points diverges (does not belong to set).
 * https://en.wikibooks.org/wiki/Fractals/Iterations_in_the_complex_plane/Mandelbrot_set/mandelbrot#Bailout_test
 */
int bailout(acb_t c, slong prec);

/**
 * For:
 * Complex inside the Mandelbrot Set  -> returns the maximum number of iterations.
 * Complex outside the Mandelbrot Set -> return the number of iterations to reach the escape condition.
 */
int execute_iterations(acb_t c, int max_iterations, slong prec, app_config config, int *period);

#endif //C_MANDELBROT_ARBITRARY_PRECISION_SET_H