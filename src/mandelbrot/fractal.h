#ifndef C_MANDELBROT_ARBITRARY_PRECISION_FRACTAL_H
#define C_MANDELBROT_ARBITRARY_PRECISION_FRACTAL_H

#include "acb.h"

typedef struct {
    int width;
    int height;
} fractal_resolution;

/**
 * For points inside Mandelbrot Set it returns MAX_ITERATIONS
 * For points outside it returns number of iterations needed to diverge.
 * @param fractal_resolution resolution
 * @param max_iterations
 * @param prec
 * @param iterations_taken_matrix
 */
void calculate_points(fractal_resolution resolution, int max_iterations, slong prec, int *iterations_taken_matrix);

#endif //C_MANDELBROT_ARBITRARY_PRECISION_FRACTAL_H