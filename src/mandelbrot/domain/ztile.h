#ifndef C_MANDELBROT_ARBITRARY_PRECISION_ZTILE_H
#define C_MANDELBROT_ARBITRARY_PRECISION_ZTILE_H

#include "zpoint.h"

/**
 * It represents the portion of the Mandelbrot Set you want to draw with complex points coordinates
 */
typedef struct {
    zpoint left_bottom_point;
    zpoint right_top_point;
} ztile;

void ztile_init(ztile *tile);

void ztile_clean(ztile *tile);

void ztile_set_from_str(
        ztile *tile,
        const char *left_bottom_re, const char *left_bottom_im,
        const char *right_top_re, const char *right_top_im,
        slong prec
);

/**
 * Initialize tile with the completed Mandelbrot from point (-2,-2) to (2,2)
 * @param tile
 * @param prec
 */
void ztile_set_completed_mandelbrot_set(ztile *tile, slong prec);

#endif //C_MANDELBROT_ARBITRARY_PRECISION_ZTILE_H