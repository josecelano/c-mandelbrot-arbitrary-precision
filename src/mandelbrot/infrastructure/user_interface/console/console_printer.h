#ifndef C_MANDELBROT_ARBITRARY_PRECISION_CONSOLE_PRINTER_H
#define C_MANDELBROT_ARBITRARY_PRECISION_CONSOLE_PRINTER_H

int console_printf(const char *format, ...);

/**
 * Flush stdout to refresh console
 */
void console_flush();

void console_print_complex(char *prefix, acb_t c);

void console_print_real(char *prefix, arb_t c);

#endif //C_MANDELBROT_ARBITRARY_PRECISION_CONSOLE_PRINTER_H
