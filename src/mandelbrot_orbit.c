#include <stdio.h>

#include "./mandelbrot/domain/complex.h"
#include "./mandelbrot/domain/formula.h"
#include "./mandelbrot/domain/fractal.h"
#include "./mandelbrot/domain/zpoint.h"
#include "./mandelbrot/infrastructure/user_interface/console/console_printer.h"
#include "./mandelbrot/infrastructure/user_interface/files/ppm_image_file.h"

void write_out_orbit(acb_t c, int max_iterations, slong precision, FILE *fp) {
    int i;
    acb_t f, z;

    acb_init(f);
    acb_init(z);

    arb_t z_re, z_im;

    arb_init(z_re);
    arb_init(z_im);

    for (i = 0; i < max_iterations; ++i) {
        mandelbrot_formula(f, z, c, precision);

        // Print row
        fprintf(fp, "%d ", i);
        arb_fprintn(fp, acb_realref(f), precision, ARB_STR_NO_RADIUS); fprintf(fp, " ");
        arb_fprintn(fp, acb_imagref(f), precision, ARB_STR_NO_RADIUS); fprintf(fp, "\n");

        acb_set(z, f);
    }

    arb_clear(z_re);
    arb_clear(z_im);

    acb_clear(f);
    acb_clear(z);
}

int main(int argc, char *argv[]) {
    char filename[] = "./output/mandelbrot-orbit.txt";
    int max_iterations = 100;
    resolution_t resolution = {256, 256};
    FILE *fp;
    int x, y, i;
    acb_t c;
    zpoint_t point;
    slong precision = 200;

    zpoint_init(&point);
    acb_init(c);

    zpoint_set_from_re_im_str(&point, "-0.1", "0.1", precision);    // Period 1
    zpoint_set_from_re_im_str(&point, "0", "1", precision);         // Period 2
    zpoint_set_from_re_im_str(&point, "-0.1", "0.7", precision);    // Period 3
    zpoint_set_from_re_im_str(&point, "-1.3", "0", precision);      // Period 4

    acb_set_from_zpoint(c, point);

    fp = fopen(filename, "wb");

    if (fp == NULL) {
        printf("Exception. Can't open file: %s\n", filename);
        abort();
    }

    write_out_orbit(c, max_iterations, precision, fp);

    fclose(fp);

    acb_clear(c);
    zpoint_clear(&point);
}