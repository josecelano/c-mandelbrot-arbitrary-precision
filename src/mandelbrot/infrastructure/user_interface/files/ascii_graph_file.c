#include <stdio.h>

#include "../../../domain/ascii_graph/ascii_graph.h"
#include "../../../domain/ascii_graph/ascii_map.h"
#include "../../../domain/calculated_point.h"
#include "../../../domain/set.h"
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
    int height = fractal_data.resolution.height;

    fp = fopen(filename, "w");

    for (y = height - 1; y >= 0; y--) {
        write_line(y, filename, fp, fractal_data, ascii_map);
        fwrite("\n", sizeof(char), 1, fp);
    }

    fclose(fp);
}

void render_ascii_graph(fractal_data_t fractal_data, ascii_map_t ascii_map) {
    char ascii_map_name[50];
    char img_filename[50];

    get_ascii_map_name(ascii_map_name, ascii_map);

    sprintf(img_filename, "./output/mandelbrot-%s-%dx%d.txt",
            ascii_map_name,
            fractal_data.resolution.width,
            fractal_data.resolution.height
    );

    render_fractal_and_write_out_the_text_file(img_filename, fractal_data, ascii_map);
}