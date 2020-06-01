#include "config.h"

void app_set_initial_config_state(config_t *config) {
    config->precision = 32;
    config->max_iterations = 100;
    config->verbose_options = 0;
    config->optimisation_options = 0;

    config->optimisation_options = config->optimisation_options | OO_MAIN_CARDIOID_DETECTION;
    config->optimisation_options = config->optimisation_options | OO_PERIOD2_DETECTION;
    config->optimisation_options = config->optimisation_options | OO_PERIODICITY_CHECKING;
}

void app_set_default_production_config(config_t *config) {
    app_set_initial_config_state(config);
}

void app_set_default_test_config(config_t *config) {
    app_set_initial_config_state(config);
}

void app_config_init(config_t *config) {
    app_set_default_production_config(config);
}

void app_config_init_test(config_t *config) {
    app_set_default_test_config(config);
}

/* Verbose options */

void app_config_enable_verbose_option(config_t *config, verbose_option_t option) {
    config->verbose_options = config->verbose_options | option;
}

void app_config_disable_verbose_option(config_t *config, verbose_option_t option) {
    config->verbose_options = config->verbose_options & ~option;
}

int app_config_verbose_option_enabled(config_t *config, verbose_option_t option) {
    return config->verbose_options & option;
}

/* Optimisation options */

void app_config_enable_optimisation_option(config_t *config, optimisation_option_t option) {
    config->optimisation_options = config->optimisation_options | option;
}

void app_config_disable_optimisation_option(config_t *config, optimisation_option_t option) {
    config->optimisation_options = config->optimisation_options & ~option;
}

int app_config_optimisation_option_enabled(config_t *config, optimisation_option_t option) {
    return config->optimisation_options & option;
}