#ifndef C_MANDELBROT_ARBITRARY_PRECISION_ASCII_GRAPH_FILE_H
#define C_MANDELBROT_ARBITRARY_PRECISION_ASCII_GRAPH_FILE_H

#include "../domain/fractal.h"

void render_and_write_out_ascii_graph(char *filename, fractal_data_t fractal_data);

void render_and_write_out_iterations_matrix(char *filename, fractal_data_t fractal_data);

#endif //C_MANDELBROT_ARBITRARY_PRECISION_ASCII_GRAPH_FILE_H
