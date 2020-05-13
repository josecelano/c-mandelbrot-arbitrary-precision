#include "../external/unity/unity.h"
#include "../external/unity/unity_fixture.h"

#include "../tests/helpers.h"
#include "../tests/unity_extension.h"

#include "../src/mandelbrot/infrastructure/ascii_graph_file.h"

TEST_GROUP(ascii_graph_should);

TEST_SETUP(ascii_graph_should) {
}

TEST_TEAR_DOWN(ascii_graph_should) {
}

void calculate_completed_mandelbrot(fractal_resolution resolution, int *iterations_taken_matrix) {
    slong prec = 32;
    int max_iterations = 100;
    ztile tile;

    ztile_init(&tile);

    ztile_set_completed_mandelbrot_set(&tile, prec);

    calculate_points(tile, resolution, max_iterations, prec, iterations_taken_matrix);

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

    fractal_resolution resolution = {256, 256};
    int *iterations_taken_matrix = malloc(resolution.width * resolution.height * sizeof *iterations_taken_matrix);

    char expected_filename[100];
    char filename[100];

    // Given the complete mandelbrot
    calculate_completed_mandelbrot(resolution, iterations_taken_matrix);

    // When we write out the ASCII graph
    sprintf(filename, "./tests/output/mandelbrot-%dx%d.txt", resolution.width, resolution.height);
    render_and_write_out_ascii_graph(filename, resolution, iterations_taken_matrix);

    // We get the expected content for the file
    sprintf(expected_filename, "./tests/fixtures/mandelbrot-%dx%d.txt", resolution.width, resolution.height);
    test_assert_txt_files_equal(expected_filename, filename);

    free(iterations_taken_matrix);
}

TEST(ascii_graph_should, generate_a_text_version_of_the_iterations_taken_matrix) {

    fractal_resolution resolution = {256, 256};
    int *iterations_taken_matrix = malloc(resolution.width * resolution.height * sizeof *iterations_taken_matrix);

    char expected_filename[100];
    char filename[100];

    // Given the complete mandelbrot
    calculate_completed_mandelbrot(resolution, iterations_taken_matrix);

    // When we write out the iterations taken matrix
    sprintf(filename, "./tests/output/mandelbrot-iter-%dx%d.txt", resolution.width, resolution.height);
    render_and_write_out_iterations_matrix(filename, resolution, iterations_taken_matrix);

    // We get the expected content for the file
    sprintf(expected_filename, "./tests/fixtures/mandelbrot-iter-%dx%d.txt", resolution.width, resolution.height);
    test_assert_txt_files_equal(expected_filename, filename);

    free(iterations_taken_matrix);
}

TEST_GROUP_RUNNER(ascii_graph_should) {
    RUN_TEST_CASE(ascii_graph_should, generate_an_ascii_version_of_the_mandelbrot_set);
    RUN_TEST_CASE(ascii_graph_should, generate_a_text_version_of_the_iterations_taken_matrix);
}