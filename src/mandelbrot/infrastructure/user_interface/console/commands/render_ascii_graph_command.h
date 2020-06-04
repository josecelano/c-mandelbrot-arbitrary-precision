#ifndef C_MANDELBROT_ARBITRARY_PRECISION_RENDER_ASCII_GRAPH_COMMAND_H
#define C_MANDELBROT_ARBITRARY_PRECISION_RENDER_ASCII_GRAPH_COMMAND_H

#include "../../../../domain/ascii_graph/ascii_map.h"

int render_ascii_graph_command(
        config_t *config,
        resolution_t resolution,
        char *left_bottom_zx, char *left_bottom_zy,
        char *top_right_zx, char *top_right_zy,
        ascii_map_t ascii_map
);

#endif //C_MANDELBROT_ARBITRARY_PRECISION_RENDER_ASCII_GRAPH_COMMAND_H
