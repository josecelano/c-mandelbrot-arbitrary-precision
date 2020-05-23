#ifndef C_MANDELBROT_ARBITRARY_PRECISION_PERIODICITY_CHECKING_H
#define C_MANDELBROT_ARBITRARY_PRECISION_PERIODICITY_CHECKING_H

#include "acb.h"
#include "arb.h"

#include "../../application/config.h"
#include "../../presentation/output.h"

/**
 * It return 1 if period is found
 */
int check_for_period(int iter, acb_t c, arb_t z_re, arb_t z_im, arb_t old_re, arb_t old_im, arb_t period_tolerance,
                     int check_counter, app_config config);

#endif //C_MANDELBROT_ARBITRARY_PRECISION_PERIODICITY_CHECKING_H
