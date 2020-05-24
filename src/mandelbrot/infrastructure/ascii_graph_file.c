#include <stdio.h>

#include "../domain/set.h"
#include "../presentation/ascii_graph.h"
#include "./ascii_graph_file.h"

void render_and_write_out_ascii_graph(char *filename, matrix_t iterations_taken_matrix) {
    int x, y, num_iter_for_pixel;
    char point_char[1];
    FILE *fp;
    resolution_t resolution = iterations_taken_matrix.resolution;

    fp = fopen(filename, "w");

    for (y = 0; y < resolution.height; y++) {
        for (x = 0; x < resolution.width; x++) {

            point_t p = {x, y};

            set_point_character(
                    point_char, p,
                    iterations_taken_matrix);

            fwrite(point_char, 1, 1, fp);
        }

        fwrite("\n", sizeof(char), 1, fp);
    }

    fclose(fp);
}

/**
 * It calculates the number of digits for a integer number. For example:
 * 123456 -> 6
 * 123    -> 3
 * 26578  -> 5
 */
unsigned int calculate_total_digits_of(unsigned int number) {
    unsigned int count = 0;

    do {
        count++;
        number /= 10;
    } while (number != 0);

    return count;
}

void write_n_spaces(FILE *fp, int n) {
    int i;
    for (i = 0; i < n; i++) {
        fwrite(" ", 1, 1, fp);
    }
}

void write_num_iter(FILE *fp, int num_iter, int num_digits) {
    char num_iter_str[50];

    sprintf(num_iter_str, "%*d", num_digits, num_iter);
    fwrite(num_iter_str, 1, num_digits, fp);
}

void render_and_write_out_iterations_matrix(char *filename, matrix_t iterations_taken_matrix) {
    int i, x, y, num_iter_for_pixel, ret;
    FILE *fp;
    resolution_t resolution = iterations_taken_matrix.resolution;
    point_t p;

    unsigned int max_for_number_of_iterations = iterations_taken_matrix.max_for_number_of_iterations;
    unsigned int num_digits;

    num_digits = calculate_total_digits_of(max_for_number_of_iterations);

    fp = fopen(filename, "w");

    for (y = 0; y < resolution.height; y++) {
        for (x = 0; x < resolution.width; x++) {

            point_set(&p, x, y);

            // TODO: WIP refactor, get fractal_calculated_point

            num_iter_for_pixel = fractal_matrix_get_num_iter_per_point(p, iterations_taken_matrix);

            ret = fractal_matrix_point_belongs_to_mandelbrot_set(p, iterations_taken_matrix);

            if (ret == INSIDE) {
                // Inside Mandelbrot Set
                write_n_spaces(fp, num_digits);
            } else {
                // Outside Mandelbrot Set
                write_num_iter(fp, num_iter_for_pixel, num_digits);
            }
        }
        fwrite("\n", sizeof(char), 1, fp);
    }

    fclose(fp);
}

