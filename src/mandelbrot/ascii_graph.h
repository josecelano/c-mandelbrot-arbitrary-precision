#ifndef C_MANDELBROT_ARBITRARY_PRECISION_ASCII_GRAPH_H
#define C_MANDELBROT_ARBITRARY_PRECISION_ASCII_GRAPH_H

#include "fractal.h"

void render_and_write_out_ascii_graph(char *filename, fractal_resolution resolution, int *iterations_taken_matrix);

void render_and_write_out_iterations_matrix(char *filename, fractal_resolution resolution, int *iterations_taken_matrix);

#endif //C_MANDELBROT_ARBITRARY_PRECISION_ASCII_GRAPH_H
