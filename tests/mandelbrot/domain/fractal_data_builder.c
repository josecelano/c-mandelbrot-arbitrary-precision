#include "../../../src/mandelbrot/domain/fractal_data.h"
#include "./fractal_data_builder.h"

void fractal_data_set_iterations_taken_for_all_points(fractal_data_t *fractal_data, int *iterations_taken) {

    int x, y;
    point_t point;
    calculated_point_t calculated_point;

    for (y = 0; y < fractal_data->resolution.height; y++) {
        for (x = 0; x < fractal_data->resolution.width; x++) {
            point_set_coordinates(&point, x, y);

            // Initial state used in all tests
            calculated_point.is_inside = FALSE;
            calculated_point.period_was_found = FALSE;
            calculated_point.period = 0;

            calculated_point.iterations_taken = (unsigned int) iterations_taken[y * fractal_data->resolution.width + x];

            fractal_data_set_calculated_point(fractal_data, point, calculated_point);
        }
    }
}