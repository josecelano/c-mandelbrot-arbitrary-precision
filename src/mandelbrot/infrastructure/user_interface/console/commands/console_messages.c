#include "../../../../domain/fractal.h"
#include "../../../../presentation/output.h"
#include "./console_messages.h"

void print_message_after_calculation(
        fractal_data_t fractal_data,
        config_t *config,
        resolution_t resolution,
        clock_t render_time
) {
    if (app_config_verbose_option_enabled(config, VO_PRINT_PERFORMANCE_DATA)) {
        print_performance_data(render_time, resolution, config);
    }

    if (app_config_verbose_option_enabled(config, VO_PRINT_FRACTAL_DATA)) {
        print_fractal_data(fractal_data);
    }
}