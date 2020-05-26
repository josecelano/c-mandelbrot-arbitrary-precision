#include <stdio.h>
#include <string.h>

#include "../domain/fractal.h"
#include "../domain/image/color.h"
#include "../domain/image/color_map.h"
#include "../domain/image/image.h"
#include "../domain/set.h"
#include "./ppm_image_file.h"

void print_ppm_image_header(FILE *fp, resolution_t resolution) {
    fprintf(fp, "P6\n");
    fprintf(fp, "%d %d %d\n", resolution.width, resolution.height, 255);
}

void write_color(FILE *fp, rgb_color color) {
    char c[3] = {(char) color.r, (char) color.g, (char) color.b};
    fwrite(c, 1, RBG_COLOR_CHAR_SIZE, fp);
}

void print_ppm_image_pixels(FILE *fp, fractal_data_t fractal_data) {
    int x, y, num_iter_for_pixel;
    int width = fractal_data.resolution.width;
    int height = fractal_data.resolution.height;
    pixel px;

    for (y = 0; y < height; y++) {
        for (x = 0; x < width; x++) {
            pixel_set_coordinates(&px, x, y);
            set_pixel_color(&px, fractal_data, BLACK_ON_WHITE);
            write_color(fp, px.color);
        }
    }
}

void render_and_write_out_image(char *filename, fractal_data_t fractal_data) {
    FILE *fp;

    fp = fopen(filename, "wb");

    print_ppm_image_header(fp, fractal_data.resolution);
    print_ppm_image_pixels(fp, fractal_data);

    fclose(fp);
}