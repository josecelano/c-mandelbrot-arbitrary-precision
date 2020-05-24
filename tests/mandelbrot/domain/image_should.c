#include "../../lib/unity/unity.h"
#include "../../lib/unity/unity_fixture.h"
#include "../../lib/helpers.h"
#include "../../lib/unity_extension.h"

#include "../../../src/mandelbrot/domain/image/color.h"
#include "../../../src/mandelbrot/domain/image/image.h"

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

/**
 * TODO: Code Review. This test is testing 2 things at he same time:
 *  1) White/Black color map is applied correctly depending of the number of iterations from iterations taken matrix.
 *  2) They 'y' coordinates for a point/pixel is inverted. We could add a test for 'get_iterations_taken_for_point'
 *     but then we have to re-think this test.
 */
TEST(image_should, calculate_the_color_for_a_given_pixel) {
    rgb_color black = {0, 0, 0};
    rgb_color white = {255, 255, 255};

    int x, y;
    int width = 3, height = 3;
    int num_iter_for_pixel;

    fractal_resolution resolution = {3, 3};
    fractal_matrix iterations_taken_matrix;
    fractal_matrix_init(&iterations_taken_matrix, resolution);

    int iterations_taken_matrix_data[9] = {
            // X  0, 1, 2  Y
            1, 1, 1,    // 0
            1, -1, 1,   // 1
            1, 1, 1     // 2
    };
    fractal_matrix_initialize_data(iterations_taken_matrix, iterations_taken_matrix_data);

    int expected_colours[9] = {
            // X 0, 1, 2    Y
            'w', 'w', 'w',  // 0
            'w', 'b', 'w',  // 1
            'w', 'w', 'w'   // 2
    };

    for (y = 0; y < 3; y++) {
        for (x = 0; x < 3; x++) {

            pixel px = {x, y};
            set_pixel_color(&px, iterations_taken_matrix);

            if (expected_colours[(y * 3) + x] == 'w') {
                test_assert_color_equal(white, px);
            }

            if (expected_colours[(y * 3) + x] == 'b') {
                test_assert_color_equal(black, px);
            }
        }
    }

    fractal_matrix_clean(&iterations_taken_matrix);
}

TEST_GROUP_RUNNER(image_should) {
    RUN_TEST_CASE(image_should, calculate_the_color_for_a_given_pixel);
}