#ifndef C_MANDELBROT_ARBITRARY_PRECISION_ASCII_GRAPH_FILE_H
#define C_MANDELBROT_ARBITRARY_PRECISION_ASCII_GRAPH_FILE_H

#include "../../../domain/fractal_data.h"
#include "../../../domain/ascii_graph/ascii_map.h"

void write_out_text_file(fractal_data_t fractal_data, ascii_map_t ascii_map, char *filename);

#endif //C_MANDELBROT_ARBITRARY_PRECISION_ASCII_GRAPH_FILE_H