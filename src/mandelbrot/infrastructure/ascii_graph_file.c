#include <stdio.h>

#include "../domain/ascii_graph/ascii_graph.h"
#include "../domain/ascii_graph/ascii_map.h"
#include "../domain/calculated_point.h"
#include "../domain/set.h"
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

    fp = fopen(filename, "w");

    for (y = 0; y < resolution.height; y++) {
        write_line(y, filename, fp, fractal_data, ascii_map);
        fwrite("\n", sizeof(char), 1, fp);
    }

    fclose(fp);
}

void render_and_write_out_ascii_graph(char *filename, fractal_data_t fractal_data) {
    render_fractal_and_write_out_the_text_file(filename, fractal_data, AT_SIGN);
}

void render_and_write_out_iterations_matrix(char *filename, fractal_data_t fractal_data) {
    render_fractal_and_write_out_the_text_file(filename, fractal_data, ITERATIONS);
}

// TODO: extract ascii_map
void render_and_write_out_full_iterations_matrix(char *filename, fractal_data_t fractal_data) {
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

            fractal_data_get_calculated_point(fractal_data, point, &calculated_point);

            write_num_iter(fp, calculated_point.iterations_taken, num_digits);
        }
        fwrite("\n", sizeof(char), 1, fp);
    }

    fclose(fp);
}

// TODO: extract ascii_map
void render_and_write_out_periods_matrix(char *filename, fractal_data_t fractal_data) {
    int i, x, y;
    FILE *fp;
    resolution_t resolution = fractal_data.resolution;
    point_t point;
    calculated_point_t calculated_point;
    char period_str[50];

    unsigned int max_for_number_of_iterations = fractal_data.max_for_number_of_iterations;
    unsigned int num_digits;

    num_digits = calculate_total_digits_of(max_for_number_of_iterations);

    fp = fopen(filename, "w");

    for (y = 0; y < resolution.height; y++) {
        for (x = 0; x < resolution.width; x++) {

            point_set_coordinates(&point, x, y);

            fractal_data_get_calculated_point(fractal_data, point, &calculated_point);

            if (calculated_point.period > 0) {
                sprintf(period_str, "%2d", calculated_point.period);
                fwrite(period_str, sizeof(char), 2, fp);
            } else {
                fwrite("  ", sizeof(char), 2, fp);
            }
        }
        fwrite("\n", sizeof(char), 1, fp);
    }

    fclose(fp);
}

