#include <stdio.h>

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