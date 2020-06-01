#ifndef C_MANDELBROT_ARBITRARY_PRECISION_ASCII_GRAPH_H
#define C_MANDELBROT_ARBITRARY_PRECISION_ASCII_GRAPH_H

#include "../fractal_data.h"
#include "../point.h"
#include "./ascii_map.h"

void write_point(point_t point, fractal_data_t fractal_data, FILE *fp, ascii_map_t ascii_map);

#endif //C_MANDELBROT_ARBITRARY_PRECISION_ASCII_GRAPH_H
