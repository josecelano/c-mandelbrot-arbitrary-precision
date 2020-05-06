#include <stdio.h>
#include "ascii_graph.h"
#include "set.h"

void render_and_write_out_ascii_graph(char *filename, fractal_resolution resolution, int *iterations_taken_matrix) {
    const char black[3] = {0, 0, 0};
    const char white[3] = {255, 255, 255};
    int x, y, num_iter_for_pixel;
    FILE *fp;

    fp = fopen(filename, "w");

    for (y = 0; y < resolution.height; y++) {
        for (x = 0; x < resolution.width; x++) {

            num_iter_for_pixel = iterations_taken_matrix[(y * resolution.width) + x];

            if (num_iter_for_pixel == MAX_ITERATIONS) {
                // Inside Mandelbrot Set
                fwrite("@", 1 , 1, fp);
            } else {
                // Outside Mandelbrot Set
                fwrite(" ", 1 , 1, fp);
            }
        }

        fwrite("\n", sizeof(char), 1, fp);
    }

    fclose(fp);
}

