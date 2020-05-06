#ifndef C_MANDELBROT_ARBITRARY_PRECISION_IMAGE_H
#define C_MANDELBROT_ARBITRARY_PRECISION_IMAGE_H

void render_and_write_out_image(char *filename, int width, int height, int *iterations_taken_matrix);

void print_ppm_image_header(FILE *fp, int width, int height);

void print_ppm_image_pixels(FILE *fp,
                            int width, int height,
                            const char *inside_color, const char *outside_color,
                            int *iterations_taken_matrix);

#endif //C_MANDELBROT_ARBITRARY_PRECISION_IMAGE_H
