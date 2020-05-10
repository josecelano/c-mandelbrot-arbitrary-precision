#include "../external/unity/unity.h"
#include "../external/unity/unity_fixture.h"
#include "../tests/unity_extension.h"
#include "../src/mandelbrot/fractal.h"

TEST_GROUP(fractal_should);

TEST_SETUP(fractal_should)
{
}

TEST_TEAR_DOWN(fractal_should)
{
}

TEST(fractal_should, calculate_complex_points_for_a_given_resolution_and_check_if_the_belong_to_the_mandelbrot_set)
{
    slong prec = 32;
    fractal_resolution resolution = {10, 10};
    int max_iterations = 200;
    int *iterations_taken_matrix;
    int x, y;
    char message[100];
    ztile tile;

    iterations_taken_matrix = malloc(resolution.width * resolution.height * sizeof *iterations_taken_matrix);

    ztile_init(&tile);
    ztile_set_completed_mandelbrot_set(&tile, prec);

    calculate_points(tile, resolution, max_iterations, prec, iterations_taken_matrix);

    ztile_clean(&tile);

    int expected_iterations_taken_matrix[100] = {
    // x 0, 1, 2, 3, 4, 5, 6, 7, 8, 9  // y
         1, 1, 1, 1, 1, 2, 1, 1, 1, 1, // 0
         1, 1, 2, 2, 2, 2, 2, 2, 2, 1, // 1
         1, 2, 2, 3, 3, 3, 2, 2, 2, 2, // 2
         1, 3, 3, 4, 6,18, 4, 2, 2, 2, // 3
         1, 3, 7, 7,-1,-1, 9, 3, 2, 2, // 4
        -1,-1,-1,-1,-1,-1, 7, 3, 2, 2, // 5
         1, 3, 7, 7,-1,-1, 9, 3, 2, 2, // 6
         1, 3, 3, 4, 6,18, 4, 2, 2, 2, // 7
         1, 2, 2, 3, 3, 3, 2, 2, 2, 2, // 8
         1, 1, 2, 2, 2, 2, 2, 2, 2, 1  // 9
    };

    for (y = 0; y < resolution.height; y++) {
        for (x = 0; x < resolution.width; x++) {
            sprintf(message, "expected number of iterations %d does not match actual %d for pixel (x,y) = (%d, %d)",
                    expected_iterations_taken_matrix[(y * resolution.width) + x],
                    iterations_taken_matrix[(y * resolution.width) + x],
                    x, y
                    );

            TEST_ASSERT_EQUAL_MESSAGE(expected_iterations_taken_matrix[(y * resolution.width) + x], iterations_taken_matrix[(y * resolution.width) + x], message);
        }
    }

    free(iterations_taken_matrix);
}

/**
 * This test was added because a bug was found when the first non symmetrical tile was rendered. In fact, the first
 * not completed Mandelbrot Set image. The bug was caused because the image was being rendered flipped horizontally.
 */
TEST(fractal_should, calculate_iterations_taken_matrix_for_a_non_symmetrical_image)
{
    slong prec = 32;
    fractal_resolution resolution = {10, 10};
    int max_iterations = 200;
    int *iterations_taken_matrix;
    int x, y;
    char message[100];
    ztile tile;

    iterations_taken_matrix = malloc(resolution.width * resolution.height * sizeof *iterations_taken_matrix);

    ztile_init(&tile);

    // Tile in the first quadrant
    ztile_set_from_str(
            &tile,
            "0.2", "0.4",
            "0.5", "0.7",
            prec
    );

    calculate_points(tile, resolution, max_iterations, prec, iterations_taken_matrix);

    ztile_clean(&tile);

    int expected_iterations_taken_matrix[100] = {
    // x 0, 1, 2, 3, 4, 5, 6, 7, 8, 9  // y
        -1,-1,-1,-1,-1,17,11, 9,10, 7, // 0
        -1,-1,-1,-1,23,29, 9, 8, 7, 6, // 1
        -1,-1,-1,-1,15,10, 8, 7, 6, 6, // 2
        -1,-1,-1,-1,-1,11, 8, 7, 6, 5, // 3
        -1,-1,-1,-1,-1,36, 9, 7, 6, 5, // 4
        -1,25,-1,-1,-1,24,10, 8, 6, 5, // 5
        15,16,27,36,-1,-1,28, 8, 6, 5, // 6
        10,10,23,25,11,17,13,17, 5, 5, // 7
         9, 8, 8, 9, 9,25, 9, 7, 5, 4, // 8
         8, 7, 7, 7, 8,10,11, 6, 5, 4  // 9
    };

    for (y = 0; y < resolution.height; y++) {
        for (x = 0; x < resolution.width; x++) {
            sprintf(message, "expected number of iterations %d does not match actual %d for pixel (x,y) = (%d, %d)",
                    expected_iterations_taken_matrix[(y * resolution.width) + x],
                    iterations_taken_matrix[(y * resolution.width) + x],
                    x, y
            );

            TEST_ASSERT_EQUAL_MESSAGE(expected_iterations_taken_matrix[(y * resolution.width) + x], iterations_taken_matrix[(y * resolution.width) + x], message);
        }
    }

    free(iterations_taken_matrix);
}

TEST_GROUP_RUNNER(fractal_should)
{
    RUN_TEST_CASE(fractal_should, calculate_complex_points_for_a_given_resolution_and_check_if_the_belong_to_the_mandelbrot_set);
    RUN_TEST_CASE(fractal_should, calculate_iterations_taken_matrix_for_a_non_symmetrical_image);
}