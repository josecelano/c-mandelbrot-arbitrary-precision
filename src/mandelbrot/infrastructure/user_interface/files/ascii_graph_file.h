#ifndef C_MANDELBROT_ARBITRARY_PRECISION_ASCII_GRAPH_FILE_H
#define C_MANDELBROT_ARBITRARY_PRECISION_ASCII_GRAPH_FILE_H

#include "../../../domain/fractal_data.h"
#include "../../../domain/ascii_graph/ascii_map.h"

void render_fractal_and_write_out_the_text_file(char *filename, fractal_data_t fractal_data, ascii_map_t ascii_map);

#endif //C_MANDELBROT_ARBITRARY_PRECISION_ASCII_GRAPH_FILE_H