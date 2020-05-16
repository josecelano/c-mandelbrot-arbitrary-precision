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
int mandelbrot_set_contains(zpoint point, int max_iterations, slong prec);

/**
 * It returns the number of iterations recursively applied to the basic Mandelbrot formula z²+c until the value diverges.
 * If MAX_ITERATIONS is reached it returns MAX_ITERATIONS, which means the point is inside the Mandelbrot Set.
 * And an integer value
 */
int mandelbrot_set_calculate_num_iterations_for(zpoint point, int max_iterations, slong prec);

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
 * https://github.com/josecelano/c-mandelbrot-arbitrary-precision/blob/master/doc/main-cardioid-checking.png
 * More info:
 * https://en.wikipedia.org/wiki/Mandelbrot_set#Main_cardioid_and_period_bulbs
 * https://en.wikibooks.org/wiki/Fractals/Iterations_in_the_complex_plane/Mandelbrot_set/mandelbrot#Cardioid_and_period-2_checking
 */
int inside_main_cardioid(acb_t c, slong prec);

#endif //C_MANDELBROT_ARBITRARY_PRECISION_SET_H