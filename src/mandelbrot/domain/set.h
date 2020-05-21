#ifndef C_MANDELBROT_ARBITRARY_PRECISION_SET_H
#define C_MANDELBROT_ARBITRARY_PRECISION_SET_H

#include "acb.h"
#include "zpoint.h"

#define MAX_ITERATIONS  -1
#define INSIDE  1
#define OUTSIDE  0

/**
 * It returns INSIDE if the point belongs to mandelbrot Set and OUTSIDE if it does not.
 */
int mandelbrot_set_contains(zpoint point, int max_iterations, slong prec, int print_periods);

/**
 * Check is the value in the matrix represents a point inside the Mandelbrot Set.
 */
int is_value_a_inside_point(int num_iter_for_pixel);

/**
 * It returns the number of iterations recursively applied to the basic Mandelbrot formula z²+c until the value diverges.
 * If MAX_ITERATIONS is reached it returns MAX_ITERATIONS, which means the point is inside the Mandelbrot Set.
 */
int mandelbrot_set_calculate_num_iterations_for(zpoint point, int max_iterations, slong prec, int print_periods);

/**
 * Bailout formula:
 * Zx²+Zy² < ER²
 * It returns 1 if we have reached the escape condition. The points diverges (does not belong to set).
 * https://en.wikibooks.org/wiki/Fractals/Iterations_in_the_complex_plane/Mandelbrot_set/mandelbrot#Bailout_test
 */
int bailout(acb_t c, slong prec);

/**
 * It returns 1 if the complex c is inside the main cardioid section (period 1) of Mandelbrot Set.
 * Formula:
 * https://github.com/josecelano/c-mandelbrot-arbitrary-precision/blob/master/doc/img/cardioid-and-period-2-checking.png
 * More info:
 * https://en.wikipedia.org/wiki/Mandelbrot_set#Main_cardioid_and_period_bulbs
 * https://en.wikibooks.org/wiki/Fractals/Iterations_in_the_complex_plane/Mandelbrot_set/mandelbrot#Cardioid_and_period-2_checking
 */
int inside_main_cardioid(acb_t c, slong prec);

/**
 * It returns 1 if the complex c is inside the period-2 bulb of Mandelbrot Set (big circle on the left of main body).
 * Formula:
 * https://github.com/josecelano/c-mandelbrot-arbitrary-precision/blob/master/doc/img/cardioid-and-period-2-checking.png
 * More info:
 * https://en.wikipedia.org/wiki/Mandelbrot_set#Main_cardioid_and_period_bulbs
 * https://en.wikibooks.org/wiki/Fractals/Iterations_in_the_complex_plane/Mandelbrot_set/mandelbrot#Cardioid_and_period-2_checking
 */
int inside_period_2_bulb(acb_t c, slong prec);

/**
 * For:
 * Complex inside the Mandelbrot Set  -> returns the maximum number of iterations.
 * Complex outside the Mandelbrot Set -> return the number of iterations to reach the escape condition.
 */
int execute_iterations(acb_t c, int max_iterations, slong prec, int print_periods, int print_iterations, int *period);

#endif //C_MANDELBROT_ARBITRARY_PRECISION_SET_H