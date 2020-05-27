#include <stdio.h>

#include "../calculated_point.h"
#include "../fractal.h"
#include "../set.h"
#include "./ascii_graph.h"
#include "./ascii_map.h"
#include "ascii_map.h"

void default_ascii_map(point_t point, fractal_data_t fractal_data, FILE *fp) {
    write_point_with_ar_sign_ascii_map(point, fractal_data, fp);
}

void write_point(point_t point, fractal_data_t fractal_data, FILE *fp, ascii_map_t ascii_map ) {
    if (ascii_map == AT_SIGN) {
        write_point_with_ar_sign_ascii_map(point, fractal_data, fp);
        return;
    }

    default_ascii_map(point, fractal_data, fp);
}