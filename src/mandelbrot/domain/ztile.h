#ifndef C_MANDELBROT_ARBITRARY_PRECISION_ZTILE_H
#define C_MANDELBROT_ARBITRARY_PRECISION_ZTILE_H

#include "../application/config.h"
#include "./zpoint.h"

/**
 * It represents the portion of the Mandelbrot Set you want to draw with complex points coordinates
 */
typedef struct {
    zpoint_t left_bottom_point;
    zpoint_t right_top_point;
} ztile_t;

void ztile_init(ztile_t *tile);

void ztile_clean(ztile_t *tile);

void ztile_set_from_str(
        ztile_t *tile,
        const char *left_bottom_re, const char *left_bottom_im,
        const char *right_top_re, const char *right_top_im,
        slong prec
);

/**
 * Initialize tile with the completed Mandelbrot from point (-2,-2) to (2,2)
 */
void ztile_set_completed_mandelbrot_set(ztile_t *tile, config_t config);

#endif //C_MANDELBROT_ARBITRARY_PRECISION_ZTILE_H