#ifndef C_MANDELBROT_ARBITRARY_PRECISION_FRACTAL_H
#define C_MANDELBROT_ARBITRARY_PRECISION_FRACTAL_H

#include "acb.h"
#include "ztile.h"

typedef struct {
    int width;
    int height;
} fractal_resolution;

/**
 * Matrix[width][height] with number of Mandelbrot formula iterations needed for each pixel to diverge.
 * -1 for point/pixel inside Mandelbrot Set.
 */
typedef struct {
    fractal_resolution resolution;
    int *data;
} fractal_matrix;

void fractal_matrix_init(fractal_matrix *iterations_taken_matrix, fractal_resolution resolution);

void fractal_matrix_clean(fractal_matrix *iterations_taken_matrix);

void fractal_matrix_initialize_data(fractal_matrix iterations_taken_matrix, int *iterations_taken);

/**
 * Iteration taken matrix is flipped horizontally, that's is to say y pixel coordinates increase from bottom to top.
 * For standard graphics format (used in PPM format) (0,0) pixel coordinates is the left top corner of the image.
 */
int fractal_matrix_get_num_iter_per_point(int x, int y, fractal_matrix iterations_taken_matrix);

/**
 * It returns INSIDE if the point in the matrix belongs to Mandelbrot Set.
 */
int fractal_matrix_point_belongs_to_mandelbrot_set(int x, int y, fractal_matrix iterations_taken_matrix);

/**
 * For points inside Mandelbrot Set it returns MAX_ITERATIONS
 * For points outside it returns number of iterations needed to diverge.
 */
void fractal_matrix_calculate_points(
        ztile tile,
        int max_iterations,
        slong prec,
        int print_progress,
        fractal_matrix *iterations_taken_matrix
);

#endif //C_MANDELBROT_ARBITRARY_PRECISION_FRACTAL_H