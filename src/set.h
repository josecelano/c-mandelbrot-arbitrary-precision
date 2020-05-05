#ifndef C_MANDELBROT_ARBITRARY_PRECISION_SET_H
#define C_MANDELBROT_ARBITRARY_PRECISION_SET_H

#include "acb.h"

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
int mandelbrot_set_contains(acb_t c, int max_iterations, slong prec);

#endif //C_MANDELBROT_ARBITRARY_PRECISION_SET_H