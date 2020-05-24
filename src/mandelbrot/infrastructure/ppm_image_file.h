#ifndef C_MANDELBROT_ARBITRARY_PRECISION_PPM_IMAGE_FILE_H
#define C_MANDELBROT_ARBITRARY_PRECISION_PPM_IMAGE_FILE_H

#include "../domain/fractal.h"

void render_and_write_out_image(char *filename, fractal_data_t fractal_data);

#endif //C_MANDELBROT_ARBITRARY_PRECISION_PPM_IMAGE_FILE_H
