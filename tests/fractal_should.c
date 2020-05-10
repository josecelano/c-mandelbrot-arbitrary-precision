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

TEST_GROUP_RUNNER(fractal_should)
{
    RUN_TEST_CASE(fractal_should, calculate_complex_points_for_a_given_resolution_and_check_if_the_belong_to_the_mandelbrot_set);
}