#ifndef C_MANDELBROT_ARBITRARY_PRECISION_FRACTAL_H
#define C_MANDELBROT_ARBITRARY_PRECISION_FRACTAL_H

#include "acb.h"
#include "ztile.h"

#include "../application/config.h"
#include "point.h"

typedef struct {
    int width;
    int height;
} resolution_t;

typedef enum {
    TRUE = 1,
    FALSE = 0
} boolean_t;

typedef struct {
    boolean_t is_inside;            // Point inside/outside Mandelbrot Set.
    unsigned int iterations_taken;  // Number of iterations done in the main fractal processing loop.
    boolean_t period_was_found;     // True if period was found.
    unsigned int period;            // if a period is found in the loop this will contain the period cycle length otherwise 0.
} calculated_point_t;

void fractal_calculated_point_init(calculated_point_t *calculated_point);

void fractal_calculated_point_set_in_main_cardioid(calculated_point_t *calculated_point);

void fractal_calculated_point_set_in_period2_bulb(calculated_point_t *calculated_point);

#endif //C_MANDELBROT_ARBITRARY_PRECISION_FRACTAL_H