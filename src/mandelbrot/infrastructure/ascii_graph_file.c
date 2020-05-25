#include <stdio.h>

#include "../domain/set.h"
#include "../presentation/ascii_graph.h"
#include "./ascii_graph_file.h"

void render_and_write_out_ascii_graph(char *filename, fractal_data_t fractal_data) {
    int x, y;
    char point_char[1];
    FILE *fp;
    resolution_t resolution = fractal_data.resolution;

    fp = fopen(filename, "w");

    for (y = 0; y < resolution.height; y++) {
        for (x = 0; x < resolution.width; x++) {

            point_t point = {x, y};

            set_point_character(point_char, point, fractal_data);

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

void render_and_write_out_iterations_matrix(char *filename, fractal_data_t fractal_data) {
    int i, x, y;
    FILE *fp;
    resolution_t resolution = fractal_data.resolution;
    point_t point;
    calculated_point_t calculated_point;

    unsigned int max_for_number_of_iterations = fractal_data.max_for_number_of_iterations;
    unsigned int num_digits;

    num_digits = calculate_total_digits_of(max_for_number_of_iterations);

    fp = fopen(filename, "w");

    for (y = 0; y < resolution.height; y++) {
        for (x = 0; x < resolution.width; x++) {

            point_set_coordinates(&point, x, y);

            fractal_matrix_get_calculated_point(fractal_data, point, &calculated_point);

            if (calculated_point.is_inside) {
                // Inside Mandelbrot Set -> print spaces
                write_n_spaces(fp, num_digits);
            } else {
                // Outside Mandelbrot Set -> print number of iterations taken
                write_num_iter(fp, calculated_point.iterations_taken, num_digits);
            }
        }
        fwrite("\n", sizeof(char), 1, fp);
    }

    fclose(fp);
}

