#ifndef C_MANDELBROT_ARBITRARY_PRECISION_MAIN_CARDIOID_DETECTION_H
#define C_MANDELBROT_ARBITRARY_PRECISION_MAIN_CARDIOID_DETECTION_H

#include "acb.h"

#include "../../application/config.h"

/**
 * It returns 1 if the complex c is inside the main cardioid section (period 1) of Mandelbrot Set.
 * Formula:
 * https://github.com/josecelano/c-mandelbrot-arbitrary-precision/blob/master/doc/img/cardioid-and-period-2-checking.png
 * More info:
 * https://en.wikipedia.org/wiki/Mandelbrot_set#Main_cardioid_and_period_bulbs
 * https://en.wikibooks.org/wiki/Fractals/Iterations_in_the_complex_plane/Mandelbrot_set/mandelbrot#Cardioid_and_period-2_checking
 */
int inside_main_cardioid(acb_t c, config_t config);

#endif //C_MANDELBROT_ARBITRARY_PRECISION_MAIN_CARDIOID_DETECTION_H
