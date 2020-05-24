#ifndef C_MANDELBROT_ARBITRARY_PRECISION_PERIODICITY_CHECKING_H
#define C_MANDELBROT_ARBITRARY_PRECISION_PERIODICITY_CHECKING_H

#include "acb.h"

#include "../../application/config.h"
#include "../fractal.h"

void execute_iterations_with_period_checking(acb_t c, config_t config, calculated_point_t *calculated_point);

#endif //C_MANDELBROT_ARBITRARY_PRECISION_PERIODICITY_CHECKING_H
