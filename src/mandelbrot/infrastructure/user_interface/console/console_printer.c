#include <stdarg.h>
#include <time.h>

#include "acb.h"
#include "arb.h"

#include "./console_printer.h"

int console_printf(const char *format, ...)
{
    va_list args;
    va_start(args, format);

    vprintf(format, args);

    va_end(args);
}

void console_flush() {
    fflush(stdout);
}

void console_print_complex(char *prefix, acb_t c) {
    flint_printf("%s", prefix);acb_printn(c, 10, 0);flint_printf("\n");
}

void console_print_real(char *prefix, arb_t c) {
    flint_printf("%s", prefix);arb_printn(c, 10, 0);flint_printf("\n");
}
