#include "config.h"

void app_set_default_config(app_config *config) {
    config->verbose_options = 0;
    config->verbose_options = config->verbose_options | PRINT_PROGRESS;
}

void app_config_init(app_config *config) {
    app_set_default_config(config);
}

void app_config_clear(app_config *config) {
}

void app_config_enable_verbose_option(app_config *config, verbose_option option) {
    config->verbose_options = config->verbose_options | option;
}

void app_config_disable_verbose_option(app_config *config, verbose_option option) {
    config->verbose_options = config->verbose_options & ~option;
}

int app_config_verbose_option_enabled(app_config *config, verbose_option option) {
    return (config->verbose_options & option) > 0;
}