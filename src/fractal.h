#ifndef C_MANDELBROT_ARBITRARY_PRECISION_FRACTAL_H
#define C_MANDELBROT_ARBITRARY_PRECISION_FRACTAL_H

#include "acb.h"

/**
 * For points inside Mandelbrot Set it returns MAX_ITERATIONS
 * For points outside it returns number of iterations needed to diverge.
 * @param res_x
 * @param res_y
 * @param max_iterations
 * @param prec
 * @param iterations_taken_matrix
 */
void calculate_points(int res_x, int res_y, int max_iterations, slong prec, int *iterations_taken_matrix);

#endif //C_MANDELBROT_ARBITRARY_PRECISION_FRACTAL_H