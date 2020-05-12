#include <stdio.h>
#include <string.h>
#include "image.h"
#include "set.h"

void render_and_write_out_image(char *filename, fractal_resolution resolution, int *iterations_taken_matrix) {
    const char black[3] = {0, 0, 0};
    const char white[3] = {255, 255, 255};
    FILE *fp;

    fp = fopen(filename, "wb");

    print_ppm_image_header(fp, resolution.width, resolution.height);
    print_ppm_image_pixels(fp, resolution.width, resolution.height, black, white, iterations_taken_matrix);

    fclose(fp);
}

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
            set_color_for_pixel(color, x, y, width, height, inside_color, outside_color, iterations_taken_matrix);
            fwrite(color, 1, RBG_COLOR_SIZE, fp);
        }
    }

    free(color);
}

/**
 * Iteration taken matrix is flipped horizontally, that's is to say y pixel coordinates increase from bottom to top.
 * For standard graphics format (used in PPM format) (0,0) pixel coordinates is the left top corner of the image.
 */
int get_iterations_taken_for_pixel(int x, int y, int width, int height, int *iterations_taken_matrix) {
    return iterations_taken_matrix[(height - 1 - y) * width + x];
}

void set_color_for_pixel(
        rgb_color color,
        int x, int y,
        int width, int height,
        const char *inside_color, const char *outside_color,
        int *iterations_taken_matrix
) {
    int num_iter_for_pixel;

    num_iter_for_pixel = get_iterations_taken_for_pixel(x, y, width, height, iterations_taken_matrix);

    if (num_iter_for_pixel == MAX_ITERATIONS) {
        strncpy(color, inside_color, RBG_COLOR_SIZE);
    } else {
        strncpy(color, outside_color, RBG_COLOR_SIZE);
    }
}

