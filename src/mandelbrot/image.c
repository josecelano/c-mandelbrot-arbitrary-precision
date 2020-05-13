#include <stdio.h>
#include <string.h>

#include "color.h"
#include "fractal.h"
#include "image.h"
#include "set.h"

void print_ppm_image_header(FILE *fp, int width, int height) {
    fprintf(fp, "P6\n");
    fprintf(fp, "%d %d %d\n", width, height, 255);
}

void print_ppm_image_pixels(
        FILE *fp,
        int width, int height,
        const char *inside_color, const char *outside_color,
        int *iterations_taken_matrix
) {
    int x, y, num_iter_for_pixel;

    char *color = malloc(RBG_COLOR_SIZE);
    int i, size = width * height;

    for (y = 0; y < height; y++) {
        for (x = 0; x < width; x++) {
            set_pixel_color(color, x, y, width, height, iterations_taken_matrix);
            fwrite(color, 1, RBG_COLOR_SIZE, fp);
        }
    }

    free(color);
}

void render_and_write_out_image(char *filename, fractal_resolution resolution, int *iterations_taken_matrix) {
    const char black[3] = {0, 0, 0};
    const char white[3] = {255, 255, 255};
    FILE *fp;

    fp = fopen(filename, "wb");

    print_ppm_image_header(fp, resolution.width, resolution.height);
    print_ppm_image_pixels(fp, resolution.width, resolution.height, black, white, iterations_taken_matrix);

    fclose(fp);
}

void set_pixel_color(
        rgb_color color,
        int x, int y,
        int width, int height, int *iterations_taken_matrix
) {
    int num_iter_for_pixel;

    num_iter_for_pixel = get_iterations_taken_for_point(x, y, width, height, iterations_taken_matrix);

    color_pixel_with_black_and_white_color_map(color, num_iter_for_pixel, iterations_taken_matrix);
}