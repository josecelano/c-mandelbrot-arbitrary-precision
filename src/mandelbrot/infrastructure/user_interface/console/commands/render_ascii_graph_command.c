#include "../../../../domain/fractal_data.h"
#include "../../../../presentation/output.h"
#include "../../files/ascii_graph_file.h"
#include "./render_ascii_graph_command.h"

int render_ascii_graph_command(
        config_t *config,
        resolution_t resolution,
        char *left_bottom_zx, char *left_bottom_zy,
        char *top_right_zx, char *top_right_zy,
        ascii_map_t ascii_map
) {
    ztile_t tile;                   // The tile we want to draw with complex points coordinates.
    fractal_data_t fractal_data;    // Matrix with calculated points.
    clock_t render_time;            // Calculate the time taken for fractal data generation.

    // TODO: validate ascii_map

    ztile_init(&tile);
    ztile_set_from_str(
            &tile,
            left_bottom_zx, left_bottom_zy,
            top_right_zx, top_right_zy,
            config->precision
    );

    /* Calculate fractal data */

    fractal_data_init(&fractal_data, resolution);
    fractal_data_calculate(&fractal_data, tile, config, &render_time);

    /* Print extra metadata */

    if (app_config_verbose_option_enabled(config, VO_PRINT_PERFORMANCE_DATA)) {
        print_performance_data(render_time, resolution, config);
    }

    if (app_config_verbose_option_enabled(config, VO_PRINT_FRACTAL_DATA)) {
        print_fractal_data(fractal_data);
    }

    /* Write out output file */

    render_ascii_graph(fractal_data, ascii_map);

    /* Clean data */

    fractal_data_clean(&fractal_data);
    ztile_clean(&tile);

    return 0;
}