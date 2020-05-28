#ifndef C_MANDELBROT_ARBITRARY_PRECISION_CONFIG_H
#define C_MANDELBROT_ARBITRARY_PRECISION_CONFIG_H

#include "acb.h"

#define ENABLED 1
#define DISABLED 0

// Verbose options
typedef enum {
    VO_PRINT_PROGRESS = 1,     // Print progress like: Progress: 99.609375%
    VO_PRINT_PERIODS = 2,      // Print period info when period checking is used
    VO_PRINT_ITERATIONS = 4,   // Print debug info for each loop iteration
} verbose_option_t;

typedef struct {
    slong precision;        // Bits of precision for C complex and real math operations library
    int max_iterations;     // Max number of iterations for Mandelbrot formula
    int verbose_options;
} config_t;

void app_config_init(config_t *config);

void app_config_init_test(config_t *config);

void app_config_enable_verbose_option(config_t *config, verbose_option_t option);

void app_config_disable_verbose_option(config_t *config, verbose_option_t option);

/**
 * Return ENABLED if verbose option is enabled.
 * @return
 */
int app_config_verbose_option_enabled(config_t config, verbose_option_t option);

#endif //C_MANDELBROT_ARBITRARY_PRECISION_CONFIG_H
