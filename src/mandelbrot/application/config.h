#ifndef C_MANDELBROT_ARBITRARY_PRECISION_CONFIG_H
#define C_MANDELBROT_ARBITRARY_PRECISION_CONFIG_H

#define ENABLED 1
#define DISABLED 0

// Verbose options
typedef enum {
    PRINT_PROGRESS = 1,
    PRINT_PERIODS = 2,
} verbose_option;

typedef struct {
    int verbose_options;
} app_config;

void app_config_init(app_config *config);

void app_config_clear(app_config *config);

void app_config_enable_verbose_option(app_config *config, verbose_option option);

void app_config_disable_verbose_option(app_config *config, verbose_option option);

/**
 * Return ENABLED if verbose option is enabled.
 * @return
 */
int app_config_verbose_option_enabled(app_config *config, verbose_option option);

#endif //C_MANDELBROT_ARBITRARY_PRECISION_CONFIG_H
