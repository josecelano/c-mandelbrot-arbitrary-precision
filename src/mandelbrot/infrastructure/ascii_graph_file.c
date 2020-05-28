#include <stdio.h>

#include "../domain/ascii_graph/ascii_graph.h"
#include "../domain/ascii_graph/ascii_map.h"
#include "../domain/calculated_point.h"
#include "../domain/set.h"
#include "./ascii_graph_file.h"

void write_line(int y, char *filename, FILE *fp, fractal_data_t fractal_data, ascii_map_t ascii_map) {
    resolution_t resolution = fractal_data.resolution;
    int x;

    for (x = 0; x < resolution.width; x++) {
        point_t point = {x, y};
        write_point(point, fractal_data, fp, ascii_map);
    }
}

void render_fractal_and_write_out_the_text_file(char *filename, fractal_data_t fractal_data, ascii_map_t ascii_map) {
    resolution_t resolution = fractal_data.resolution;
    FILE *fp;
    int x, y;

    fp = fopen(filename, "w");

    for (y = 0; y < resolution.height; y++) {
        write_line(y, filename, fp, fractal_data, ascii_map);
        fwrite("\n", sizeof(char), 1, fp);
    }

    fclose(fp);
}