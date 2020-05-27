#ifndef C_MANDELBROT_ARBITRARY_PRECISION_ASCII_MAP_H
#define C_MANDELBROT_ARBITRARY_PRECISION_ASCII_MAP_H

#include "../fractal_data.h"
#include "../point.h"

// This is the same concept as color_map but for characters in a txt file instead of pixel inside an image.
typedef enum {
    AT_SIGN = 0,    // Use @ char for points inside Mandelbrot Set
    ITERATIONS = 1, // 3 digits with the number of iterations taken for that point
} ascii_map_t;

void write_point_with_ar_sign_ascii_map(point_t point, fractal_data_t fractal_data, FILE *fp);

void write_point_with_iterations_ascii_map(point_t point, fractal_data_t fractal_data, FILE *fp);

// TODO: make private when refactor it's finished
void write_num_iter(FILE *fp, int num_iter, int num_digits);
unsigned int calculate_total_digits_of(unsigned int number);

#endif //C_MANDELBROT_ARBITRARY_PRECISION_ASCII_MAP_H
