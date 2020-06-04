#include <stdio.h>
#include <string.h>

#include "../calculated_point.h"
#include "../fractal.h"
#include "../set.h"
#include "./ascii_graph.h"
#include "./ascii_map.h"

void write_point_with_ar_sign_ascii_map(point_t point, fractal_data_t fractal_data, FILE *fp) {
    char point_char[1];
    calculated_point_t calculated_point;

    fractal_data_get_calculated_point(fractal_data, point, &calculated_point);

    if (calculated_point.is_inside) {
        fwrite("@", 1, 1, fp);
        return;
    }

    fwrite(" ", 1, 1, fp);
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

void write_point_with_iterations_ascii_map(point_t point, fractal_data_t fractal_data, FILE *fp) {
    unsigned int max_for_number_of_iterations, num_digits;
    calculated_point_t calculated_point;

    max_for_number_of_iterations = fractal_data.max_for_number_of_iterations;
    num_digits = calculate_total_digits_of(max_for_number_of_iterations);

    fractal_data_get_calculated_point(fractal_data, point, &calculated_point);

    if (calculated_point.is_inside) {
        // Inside Mandelbrot Set -> print blank spaces
        write_n_spaces(fp, num_digits);
    } else {
        // Outside Mandelbrot Set -> print number of iterations taken
        write_num_iter(fp, calculated_point.iterations_taken, num_digits);
    }
}

void write_point_with_full_iterations_ascii_map(point_t point, fractal_data_t fractal_data, FILE *fp) {
    unsigned int max_for_number_of_iterations, num_digits;
    calculated_point_t calculated_point;

    max_for_number_of_iterations = fractal_data.max_for_number_of_iterations;
    num_digits = calculate_total_digits_of(max_for_number_of_iterations);

    fractal_data_get_calculated_point(fractal_data, point, &calculated_point);
    write_num_iter(fp, calculated_point.iterations_taken, num_digits);
}

void write_point_with_periods_ascii_map(point_t point, fractal_data_t fractal_data, FILE *fp) {
    char period_str[50];
    calculated_point_t calculated_point;

    fractal_data_get_calculated_point(fractal_data, point, &calculated_point);

    if (calculated_point.period > 0) {
        sprintf(period_str, "%2d", calculated_point.period);
        fwrite(period_str, sizeof(char), 2, fp);
    } else {
        fwrite("  ", sizeof(char), 2, fp);
    }
}

void get_ascii_map_name(char *ascii_map_name, ascii_map_t ascii_map) {
    switch (ascii_map) {
        case AM_AT_SIGN:
            strcpy(ascii_map_name, "at-sign");
            break;
        case AM_ITERATIONS:
            strcpy(ascii_map_name, "iterations");
            break;
        case AM_FULL_ITERATIONS:
            strcpy(ascii_map_name, "full-iterations");
            break;
        case AM_PERIODS:
            strcpy(ascii_map_name, "periods");
            break;
        default:
            printf("Exception. Invalid ascii map %d\n", ascii_map);
            abort();
    }
}