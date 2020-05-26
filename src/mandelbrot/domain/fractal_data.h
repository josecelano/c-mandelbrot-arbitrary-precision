#ifndef C_MANDELBROT_ARBITRARY_PRECISION_FRACTAL_DATA_H
#define C_MANDELBROT_ARBITRARY_PRECISION_FRACTAL_DATA_H

#include "./calculated_point.h"
#include "./fractal.h"
#include "./point.h"
#include "./ztile.h"

typedef struct {
    resolution_t resolution;
    unsigned int number_of_found_periods;       // Number of periods found when it's used the periods checking optimisation.
    unsigned int max_for_number_of_iterations;  // Max number of iterations done of all points.
    calculated_point_t *calculated_points;      // Array of calculated points.
} fractal_data_t;

void fractal_data_init(fractal_data_t *fractal_data, resolution_t resolution);

void fractal_data_clean(fractal_data_t *fractal_data);

// TODO: Code Review. It's only used in TEST code. Replace by a builder? And include the rest of members.
void fractal_data_initialize_iterations_taken(fractal_data_t *fractal_data, int *iterations_taken);

void fractal_data_set_calculated_point(fractal_data_t *fractal_data, point_t point, calculated_point_t calculated_point);

void fractal_data_get_calculated_point(fractal_data_t fractal_data, point_t point, calculated_point_t *calculated_point);

void fractal_data_calculate_points(fractal_data_t *fractal_data, ztile_t tile, config_t config);

#endif //C_MANDELBROT_ARBITRARY_PRECISION_FRACTAL_DATA_H