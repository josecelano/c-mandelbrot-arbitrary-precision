#ifndef C_MANDELBROT_ARBITRARY_PRECISION_SET_H
#define C_MANDELBROT_ARBITRARY_PRECISION_SET_H

#include "acb.h"

#include "../application/config.h"
#include "./calculated_point.h"
#include "./fractal.h"
#include "./optimisation/main_cardioid_detection.h"
#include "./zpoint.h"

#define MAX_ITERATIONS  -1
#define INSIDE  1
#define OUTSIDE  0

/**
 * It returns INSIDE if the point belongs to mandelbrot Set and OUTSIDE if it does not.
 */
int mandelbrot_set_contains(zpoint_t point, config_t *config);

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
void mandelbrot_set_calculate_point(zpoint_t point, config_t *config, calculated_point_t *calculated_point);

#endif //C_MANDELBROT_ARBITRARY_PRECISION_SET_H