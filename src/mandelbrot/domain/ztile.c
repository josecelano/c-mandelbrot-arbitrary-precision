#include "ztile.h"
#include "zpoint.h"

void ztile_init(ztile_t *tile) {
    zpoint_init(&tile->left_bottom_point);
    zpoint_init(&tile->right_top_point);
}

void ztile_clean(ztile_t *tile) {
    zpoint_clean(&tile->left_bottom_point);
    zpoint_clean(&tile->right_top_point);
}

void ztile_set_from_str(
        ztile_t *tile,
        const char *left_bottom_re, const char *left_bottom_im,
        const char *right_top_re, const char *right_top_im,
        slong prec
) {
    // TODO: validate points
    zpoint_set_from_re_im_str(&tile->left_bottom_point, left_bottom_re, left_bottom_im, prec);
    zpoint_set_from_re_im_str(&tile->right_top_point, right_top_re, right_top_im, prec);
}

void ztile_set_completed_mandelbrot_set(ztile_t *tile, config_t config) {
    ztile_set_from_str(
            tile,
            "-2", "-2",
            "2", "2",
            config.precision
    );
}



