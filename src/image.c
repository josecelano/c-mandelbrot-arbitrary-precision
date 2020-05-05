#include <stdio.h>
#include "image.h"
#include "set.h"

void render_and_write_out_image(char *filename, int width, int height, int *iterations_map) {
    const char black[3] = {0, 0, 0};
    const char white[3] = {255, 255, 255};
    FILE *fp;

    fp = fopen(filename, "wb");

    print_ppm_image_header(fp, width, height);
    print_ppm_image_pixels(fp, width, height, black, white, iterations_map);

    fclose(fp);
}

void print_ppm_image_header(FILE *fp, int width, int height) {
    fprintf(fp, "P6\n");
    fprintf(fp, "%d %d %d\n", width, height, 255);
}

void print_ppm_image_pixels(FILE *fp,
                            int width, int height,
                            const char *inside_color, const char *outside_color,
                            int *iterations_map) {
    int x, y, num_iter_for_pixel;

    for (y = 0; y < height; y++) {
        for (x = 0; x < width; x++) {

            num_iter_for_pixel = iterations_map[(y * width) + x];

            if (num_iter_for_pixel == MAX_ITERATIONS) {
                // Inside Mandelbrot Set
                fwrite(inside_color, 1, sizeof(char) * 3, fp);
            } else {
                // Outside Mandelbrot Set
                fwrite(outside_color, 1, sizeof(char) * 3, fp);
            }
        }
    }
}

