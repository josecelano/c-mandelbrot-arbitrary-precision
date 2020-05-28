#include "config.h"

void app_set_default_production_config(config_t *config) {
    config->precision = 32;
    config->max_iterations = 100;
    config->verbose_options = 0;
    config->verbose_options = config->verbose_options | VO_PRINT_PROGRESS;
}

void app_set_default_test_config(config_t *config) {
    config->precision = 32;
    config->max_iterations = 100;
    config->verbose_options = 0;
}

void app_config_init(config_t *config) {
    app_set_default_production_config(config);
}

void app_config_init_test(config_t *config) {
    app_set_default_test_config(config);
}

void app_config_enable_verbose_option(config_t *config, verbose_option_t option) {
    config->verbose_options = config->verbose_options | option;
}

void app_config_disable_verbose_option(config_t *config, verbose_option_t option) {
    config->verbose_options = config->verbose_options & ~option;
}

int app_config_verbose_option_enabled(config_t config, verbose_option_t option) {
    return (config.verbose_options & option) > 0;
}