#ifndef C_MANDELBROT_ARBITRARY_PRECISION_SET_H
#define C_MANDELBROT_ARBITRARY_PRECISION_SET_H

#include "acb.h"
#include "zpoint.h"

#define MAX_ITERATIONS  -1

/**
 * It returns the number of iterations recursively applied to the basic Mandelbrot formula z²+c until the value diverges.
 * If MAX_ITERATIONS is reached it returns MAX_ITERATIONS, which means the point is inside the Mandelbrot Set.
 * And an integer value
 * @param c
 * @param max_iterations
 * @param prec
 * @return
 */
int mandelbrot_set_contains(zpoint point, int max_iterations, slong prec);

/**
 * Bailout formula:
 * Zx²+Zy² < ER²
 * It returns 1 if we have reached the escape condition. The points diverges (does not belong to set).
 * https://en.wikibooks.org/wiki/Fractals/Iterations_in_the_complex_plane/Mandelbrot_set/mandelbrot#Bailout_test
 */
int bailout(acb_t c, slong prec);

#endif //C_MANDELBROT_ARBITRARY_PRECISION_SET_H