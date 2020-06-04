#ifndef C_MANDELBROT_ARBITRARY_PRECISION_PPM_IMAGE_FILE_H
#define C_MANDELBROT_ARBITRARY_PRECISION_PPM_IMAGE_FILE_H

#include "../../../domain/fractal.h"
#include "../../../domain/fractal_data.h"
#include "../../../domain/image/color_map.h"

void render_and_write_out_image(char *filename, fractal_data_t fractal_data, color_map_t color_map);

void render_ppm_image(fractal_data_t fractal_data, color_map_t color_map);

#endif //C_MANDELBROT_ARBITRARY_PRECISION_PPM_IMAGE_FILE_H
