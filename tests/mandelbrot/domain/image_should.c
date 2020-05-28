#include "../../lib/unity/unity.h"
#include "../../lib/unity/unity_fixture.h"
#include "../../lib/helpers.h"
#include "../../lib/unity_extension.h"

#include "../../../src/mandelbrot/domain/image/color.h"
#include "../../../src/mandelbrot/domain/image/image.h"
#include "./fractal_data_builder.h"

/* TODO:
 *  1) Add a test for a non symmetrical image.
 *  2) Actually this test is testing that the color map is applied correctly. We can use 2 different color maps.
 *     On the other hand the function 'fractal_data_set_iterations_taken_for_all_points' was used when we stored
 *     only the number of iterations. Now we store calculated_point and we should create a new builder.
 *     That builder it seems to be used in TEST code. Maybe we should create a constructor and pass all calculated
 *     point with 2 matrix:
 *         * number of iterations
 *         * point inside/outside
 *     Otherwise we could continue using an special value (-1) for number of iterations to represent a point inside.
 */

TEST_GROUP(image_should);

TEST_SETUP(image_should) {
}

TEST_TEAR_DOWN(image_should) {
}

void test_assert_color_equal(rgb_color expected, pixel px) {
    char message[100];
    rgb_color actual = px.color;

    sprintf(message, "Pixel color { %d, %d, %d} does not match expected { %d, %d, %d} for pixel (x,y) = (%d, %d)",
            actual.r, actual.g, actual.b, expected.r, expected.g, expected.b, px.x, px.y);
    TEST_ASSERT_EQUAL_MESSAGE(expected.r, actual.r, message); // R
    TEST_ASSERT_EQUAL_MESSAGE(expected.g, actual.g, message); // G
    TEST_ASSERT_EQUAL_MESSAGE(expected.b, actual.b, message); // B
}

TEST(image_should, calculate_the_color_for_a_given_pixel) {
    rgb_color black = {0, 0, 0};
    rgb_color white = {255, 255, 255};

    int x, y;
    int width = 3, height = 3;
    int num_iter_for_pixel;

    resolution_t resolution = {3, 3};
    fractal_data_t fractal_data;
    fractal_data_init(&fractal_data, resolution);

    int iterations_taken_matrix_data[9] = {
    // X    0,  1,  2    // Y
            1,  1,  1,   // 0
            1,100,  1,   // 1
            1,  1,  1    // 2
    };
    fractal_data_set_iterations_taken_for_all_points(&fractal_data, iterations_taken_matrix_data);

    point_t point;
    point_set_coordinates(&point, 1, 1);

    calculated_point_t calculated_point = {
            .is_inside = TRUE,
            .iterations_taken = 100,
            .period_was_found = FALSE,
            .period = 0
    };
    fractal_data_set_calculated_point(&fractal_data, point, calculated_point);

    int expected_colours[9] = {
    // X      0,   1,   2   // Y
            'w', 'w', 'w',  // 0
            'w', 'b', 'w',  // 1
            'w', 'w', 'w'   // 2
    };

    for (y = 0; y < 3; y++) {
        for (x = 0; x < 3; x++) {

            pixel px = {x, y};
            set_pixel_color(&px, fractal_data, CM_BLACK_ON_WHITE);

            if (expected_colours[(y * 3) + x] == 'w') {
                test_assert_color_equal(white, px);
            }

            if (expected_colours[(y * 3) + x] == 'b') {
                test_assert_color_equal(black, px);
            }
        }
    }

    fractal_data_clean(&fractal_data);
}

TEST_GROUP_RUNNER(image_should) {
    RUN_TEST_CASE(image_should, calculate_the_color_for_a_given_pixel);
}