#include <string.h>
#include <stdio.h>

#include "acb.h"
#include "arb.h"

#include "../presentation/output.h"
#include "./complex.h"
#include "./fractal.h"
#include "./optimisation/main_cardioid_detection.h"
#include "./optimisation/period2_detection.h"
#include "./optimisation/periodicity_checking.h"
#include "./set.h"
#include "./zpoint.h"
#include "./ztile.h"

void fractal_calculated_point_init(calculated_point_t *calculated_point) {
    calculated_point->is_inside = TRUE;
    calculated_point->iterations_taken = 0;
    calculated_point->period_was_found = FALSE;
    calculated_point->period = 0;
}

void fractal_calculated_point_set_in_main_cardioid(calculated_point_t *calculated_point) {
    calculated_point->is_inside = TRUE;
    calculated_point->iterations_taken = 0;
    calculated_point->period_was_found = TRUE;
    calculated_point->period = 1;
}

void fractal_calculated_point_set_in_period2_bulb(calculated_point_t *calculated_point) {
    calculated_point->is_inside = TRUE;
    calculated_point->iterations_taken = 0;
    calculated_point->period_was_found = TRUE;
    calculated_point->period = 2;
}

