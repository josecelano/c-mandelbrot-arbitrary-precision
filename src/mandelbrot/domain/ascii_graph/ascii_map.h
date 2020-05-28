#ifndef C_MANDELBROT_ARBITRARY_PRECISION_ASCII_MAP_H
#define C_MANDELBROT_ARBITRARY_PRECISION_ASCII_MAP_H

#include "../fractal_data.h"
#include "../point.h"

// This is the same concept as color_map but for characters in a txt file instead of pixel inside an image.
typedef enum {
    AM_AT_SIGN = 0,            // Use @ char for points inside Mandelbrot Set
    AM_ITERATIONS = 1,         // 3 digits with the number of iterations taken for that point
    AM_FULL_ITERATIONS = 2,    // 3 digits with the number of iterations taken for that point (including points inside)
    AM_PERIODS = 3,            // 1 digits with the periods cycle length (only points inside)
} ascii_map_t;

void write_point_with_ar_sign_ascii_map(point_t point, fractal_data_t fractal_data, FILE *fp);

void write_point_with_iterations_ascii_map(point_t point, fractal_data_t fractal_data, FILE *fp);

void write_point_with_full_iterations_ascii_map(point_t point, fractal_data_t fractal_data, FILE *fp);

void write_point_with_periods_ascii_map(point_t point, fractal_data_t fractal_data, FILE *fp);

#endif //C_MANDELBROT_ARBITRARY_PRECISION_ASCII_MAP_H
