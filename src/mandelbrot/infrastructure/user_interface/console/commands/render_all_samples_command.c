#include "../../../../domain/fractal_data.h"
#include "../../../../presentation/output.h"
#include "../../files/ascii_graph_file.h"
#include "../../files/ppm_image_file.h"
#include "./console_messages.h"
#include "./render_all_samples_command.h"

void render_all_samples(fractal_data_t fractal_data) {
    // Render images
    render_ppm_image(fractal_data, CM_BLACK_ON_WHITE);
    render_ppm_image(fractal_data, CM_WHITE_ON_BLACK);
    render_ppm_image(fractal_data, CM_COLORED_PERIODS);

    // Render ascii graphs
    render_ascii_graph(fractal_data, AM_AT_SIGN);
    render_ascii_graph(fractal_data, AM_ITERATIONS);
    render_ascii_graph(fractal_data, AM_FULL_ITERATIONS);
    render_ascii_graph(fractal_data, AM_PERIODS);
}

void set_configuration_for_samples(config_t *config) {
    app_config_enable_optimisation_option(config, OO_MAIN_CARDIOID_DETECTION);
    app_config_enable_optimisation_option(config, OO_PERIOD2_DETECTION);
    app_config_enable_optimisation_option(config, OO_PERIODICITY_CHECKING);
}

int render_all_samples_command(config_t *config, resolution_t resolution) {
    ztile_t tile;                   // The tile we want to draw with complex points coordinates.
    fractal_data_t fractal_data;    // Matrix with calculated points.
    clock_t render_time;            // Calculate the time taken for fractal data generation.

    set_configuration_for_samples(config);

    ztile_init(&tile);
    ztile_set_completed_mandelbrot_set(&tile, config);

    fractal_data_init(&fractal_data, resolution);
    fractal_data_calculate(&fractal_data, tile, config, &render_time);

    print_message_after_calculation(fractal_data, config, resolution, render_time);

    render_all_samples(fractal_data);

    fractal_data_clean(&fractal_data);
    ztile_clean(&tile);

    return 0;
}