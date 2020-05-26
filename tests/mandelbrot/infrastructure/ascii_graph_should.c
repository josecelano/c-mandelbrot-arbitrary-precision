#include "../../lib/unity/unity.h"
#include "../../lib/unity/unity_fixture.h"

#include "../../lib/helpers.h"
#include "../../lib/unity_extension.h"

#include "../../../src/mandelbrot/infrastructure/ascii_graph_file.h"

TEST_GROUP(ascii_graph_should);

TEST_SETUP(ascii_graph_should) {
}

TEST_TEAR_DOWN(ascii_graph_should) {
}

void calculate_completed_mandelbrot(resolution_t resolution, fractal_data_t *fractal_data) {
    ztile_t tile;

    config_t config;
    app_config_init_test(&config);

    ztile_init(&tile);

    ztile_set_completed_mandelbrot_set(&tile, config);

    fractal_data_calculate_points(fractal_data, tile, config);

    ztile_clean(&tile);
}

void test_assert_txt_files_equal(char *expected_filename, char *actual_filename) {
    int line, col, equal;
    char message[300];

    equal = txt_files_are_equal(expected_filename, actual_filename, &line, &col);

    sprintf(message, "%s does not have the same content as %s. First difference at line %d column %d.",
            actual_filename, expected_filename, line, col);

    TEST_ASSERT_TRUE_MESSAGE(equal, message);
}

TEST(ascii_graph_should, generate_an_ascii_version_of_the_mandelbrot_set) {

    resolution_t resolution = {256, 256};
    fractal_data_t fractal_data;

    fractal_data_init(&fractal_data, resolution);

    char expected_filename[100];
    char filename[100];

    // Given the complete mandelbrot
    calculate_completed_mandelbrot(resolution, &fractal_data);

    // When we write out the ASCII graph
    sprintf(filename, "./tests/output/mandelbrot-%dx%d.txt", resolution.width, resolution.height);
    render_and_write_out_ascii_graph(filename, fractal_data);

    // We get the expected content for the file
    sprintf(expected_filename, "./tests/fixtures/mandelbrot-%dx%d.txt", resolution.width, resolution.height);
    test_assert_txt_files_equal(expected_filename, filename);

    fractal_data_clean(&fractal_data);
}

TEST(ascii_graph_should, generate_a_text_version_of_the_iterations_taken_matrix) {

    resolution_t resolution = {256, 256};
    fractal_data_t fractal_data;

    fractal_data_init(&fractal_data, resolution);

    char expected_filename[100];
    char filename[100];

    // Given the complete mandelbrot
    calculate_completed_mandelbrot(resolution, &fractal_data);

    // When we write out the iterations taken matrix
    sprintf(filename, "./tests/output/mandelbrot-iter-%dx%d.txt", resolution.width, resolution.height);
    render_and_write_out_iterations_matrix(filename, fractal_data);

    // We get the expected content for the file
    sprintf(expected_filename, "./tests/fixtures/mandelbrot-iter-%dx%d.txt", resolution.width, resolution.height);
    test_assert_txt_files_equal(expected_filename, filename);

    fractal_data_clean(&fractal_data);
}

TEST_GROUP_RUNNER(ascii_graph_should) {
    RUN_TEST_CASE(ascii_graph_should, generate_an_ascii_version_of_the_mandelbrot_set);
    RUN_TEST_CASE(ascii_graph_should, generate_a_text_version_of_the_iterations_taken_matrix);
}