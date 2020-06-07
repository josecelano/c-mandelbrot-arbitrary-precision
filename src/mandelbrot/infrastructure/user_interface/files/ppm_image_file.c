#include <stdio.h>
#include <string.h>

#include "../../../domain/fractal.h"
#include "../../../domain/image/color.h"
#include "../../../domain/image/color_map.h"
#include "../../../domain/image/image.h"
#include "../../../domain/set.h"
#include "./ppm_image_file.h"

void print_ppm_image_header(FILE *fp, resolution_t resolution) {
    fprintf(fp, "P6\n");
    fprintf(fp, "%d %d %d\n", resolution.width, resolution.height, 255);
}

void write_color(FILE *fp, rgb_color color) {
    char c[3] = {(char) color.r, (char) color.g, (char) color.b};
    fwrite(c, 1, RBG_COLOR_CHAR_SIZE, fp);
}

void print_ppm_image_pixels(FILE *fp, fractal_data_t fractal_data, color_map_t color_map) {
    int x, y, num_iter_for_pixel;
    int width = fractal_data.resolution.width;
    int height = fractal_data.resolution.height;
    pixel px;

    for (y = height - 1; y >= 0; y--) {
        for (x = 0; x < width; x++) {
            pixel_set_coordinates(&px, x, y);
            set_pixel_color(&px, fractal_data, color_map);
            write_color(fp, px.color);
        }
    }
}

void render_and_write_out_image(char *filename, fractal_data_t fractal_data, color_map_t color_map) {
    FILE *fp;

    fp = fopen(filename, "wb");

    print_ppm_image_header(fp, fractal_data.resolution);
    print_ppm_image_pixels(fp, fractal_data, color_map);

    fclose(fp);
}

void render_ppm_image(fractal_data_t fractal_data, color_map_t color_map) {
    char color_map_name[50];
    char img_filename[50];

    get_color_map_name(color_map_name, color_map);

    sprintf(img_filename, "./output/mandelbrot-%s-%dx%d.ppm",
            color_map_name,
            fractal_data.resolution.width,
            fractal_data.resolution.height
    );

    render_and_write_out_image(img_filename, fractal_data, color_map);
}