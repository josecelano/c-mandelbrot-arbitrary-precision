#ifndef C_MANDELBROT_ARBITRARY_PRECISION_RENDER_PPM_IMAGE_COMMAND_H
#define C_MANDELBROT_ARBITRARY_PRECISION_RENDER_PPM_IMAGE_COMMAND_H

#include "../../../../domain/image/color_map.h"

int render_ppm_image_command(
        config_t *config,
        resolution_t resolution,
        char *left_bottom_zx, char *left_bottom_zy,
        char *top_right_zx, char *top_right_zy,
        color_map_t color_map
);

#endif //C_MANDELBROT_ARBITRARY_PRECISION_RENDER_PPM_IMAGE_COMMAND_H
