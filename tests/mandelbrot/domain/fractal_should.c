#include "../../lib/unity/unity.h"
#include "../../lib/unity/unity_fixture.h"
#include "../../lib/unity_extension.h"

#include "../../../src/mandelbrot/domain/fractal_data.h"
#include "./fractal_data_builder.h"

TEST_GROUP(fractal_should);

TEST_SETUP(fractal_should) {
}

TEST_TEAR_DOWN(fractal_should) {
}

void test_assert_equal_iteration_matrix(fractal_data_t expected_fractal_data, fractal_data_t fractal_data) {
    int x, y, expected_num_iter, num_iter;
    char message[100];
    resolution_t resolution = fractal_data.resolution;
    point_t point;
    calculated_point_t expected_calculated_point, calculated_point;

    for (y = 0; y < resolution.height; y++) {
        for (x = 0; x < resolution.width; x++) {

            point_set_coordinates(&point, x, y);

            fractal_data_get_calculated_point(expected_fractal_data, point, &expected_calculated_point);
            fractal_data_get_calculated_point(fractal_data, point, &calculated_point);

            expected_num_iter = expected_calculated_point.iterations_taken;
            num_iter = calculated_point.iterations_taken;

            sprintf(message, " Expected number of iterations %d does not match actual %d for pixel (x,y) = (%d, %d)",
                    expected_num_iter,
                    num_iter,
                    x, y
            );

            TEST_ASSERT_EQUAL_MESSAGE(expected_num_iter, num_iter, message);
        }
    }
}

TEST(fractal_should, calculate_complex_points_for_a_given_resolution_and_check_if_the_belong_to_the_mandelbrot_set) {
    int x, y;
    char message[100];

    config_t config;
    app_config_init_test(&config);

    ztile_t tile;
    resolution_t resolution = {10, 10};
    fractal_data_t expected_fractal_data;
    fractal_data_t fractal_data;

    fractal_data_init(&expected_fractal_data, resolution);
    fractal_data_init(&fractal_data, resolution);

    int expected_iterations_taken_matrix_data[100] = {
        //x  0,  1,  2,  3,  4,  5, 6, 7, 8, 9  // y
             1,  1,  1,  1,  1,  2, 1, 1, 1, 1, // 0
             1,  1,  2,  2,  2,  2, 2, 2, 2, 1, // 1
             1,  2,  2,  3,  3,  3, 2, 2, 2, 2, // 2
             1,  3,  3,  4,  6, 18, 4, 2, 2, 2, // 3
             1,  3,  7,  7,  0,  0, 9, 3, 2, 2, // 4
             3,100,  0,  0,  0,  0, 7, 3, 2, 2, // 5
             1,  3,  7,  7,  0,  0, 9, 3, 2, 2, // 6
             1,  3,  3,  4,  6, 18, 4, 2, 2, 2, // 7
             1,  2,  2,  3,  3,  3, 2, 2, 2, 2, // 8
             1,  1,  2,  2,  2,  2, 2, 2, 2, 1  // 9
    };
    fractal_data_set_iterations_taken_for_all_points(&expected_fractal_data, expected_iterations_taken_matrix_data);

    ztile_init(&tile);
    ztile_set_completed_mandelbrot_set(&tile, config);

    fractal_data_calculate_points(&fractal_data, tile, config);

    ztile_clean(&tile);

    test_assert_equal_iteration_matrix(expected_fractal_data, fractal_data);

    fractal_data_clean(&expected_fractal_data);
    fractal_data_clean(&fractal_data);
}

/**
 * This test was added because a bug was found when the first non symmetrical tile was rendered. In fact, the first
 * not completed Mandelbrot Set image. The bug was caused because the image was being rendered flipped horizontally.
 */
TEST(fractal_should, calculate_iterations_taken_matrix_for_a_non_symmetrical_image) {
    int x, y;
    char message[100];

    config_t config;
    app_config_init_test(&config);

    ztile_t tile;
    resolution_t resolution = {10, 10};
    fractal_data_t expected_fractal_data;
    fractal_data_t fractal_data;

    fractal_data_init(&expected_fractal_data, resolution);
    fractal_data_init(&fractal_data, resolution);

    ztile_init(&tile);

    // Tile in the first quadrant
    ztile_set_from_str(
            &tile,
            "0.2", "0.4",
            "0.5", "0.7",
            config.precision
    );

    fractal_data_calculate_points(&fractal_data, tile, config);

    ztile_clean(&tile);

    int expected_iterations_taken_matrix_data[100] = {
        // x 0,  1,  2,  3,  4,  5,  6,  7,  8, 9   // y
             0,  0,  0,  0,  0, 17, 11,  9, 10, 7,  // 0
             0,  0,  0,  0, 23, 29,  9,  8,  7, 6,  // 1
             0,  0,  0,100, 15, 10,  8,  7,  6, 6,  // 2
             0,  0,100,100,100, 11,  8,  7,  6, 5,  // 3
             0,100, 36, 36,100, 36,  9,  7,  6, 5,  // 4
           100, 25, 40, 36,100, 24, 10,  8,  6, 5,  // 5
            15, 16, 27, 36,100,100, 28,  8,  6, 5,  // 6
            10, 10, 23, 25, 11, 17, 13, 17,  5, 5,  // 7
             9,  8,  8,  9,  9, 25,  9,  7,  5, 4,  // 8
             8,  7,  7,  7,  8, 10, 11,  6,  5, 4   // 9
    };
    fractal_data_set_iterations_taken_for_all_points(&expected_fractal_data, expected_iterations_taken_matrix_data);

    test_assert_equal_iteration_matrix(expected_fractal_data, fractal_data);

    fractal_data_clean(&expected_fractal_data);
    fractal_data_clean(&fractal_data);
}

TEST_GROUP_RUNNER(fractal_should) {
    RUN_TEST_CASE(fractal_should,
                  calculate_complex_points_for_a_given_resolution_and_check_if_the_belong_to_the_mandelbrot_set);
    RUN_TEST_CASE(fractal_should, calculate_iterations_taken_matrix_for_a_non_symmetrical_image);
}