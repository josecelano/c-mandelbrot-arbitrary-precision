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
    char* image;
    int *iterations_taken_matrix;
    FILE *fp;
    int x, y;
    char message[100];

    image = malloc(resolution.width * resolution.height * 3);
    iterations_taken_matrix = malloc(resolution.width * resolution.height * sizeof *iterations_taken_matrix);

    calculate_points(resolution, max_iterations, prec, iterations_taken_matrix);

    int expected_iterations_taken_matrix[100] = {
    // x 0, 1, 2, 3, 4, 5, 6, 7, 8, 9  // y
         1, 1, 1, 1, 1, 1, 1, 1, 1, 1, // 0
         1, 1, 1, 1, 1, 1, 1, 1, 1, 1, // 1
         1, 1, 2, 2, 2, 2, 1, 1, 1, 1, // 2
         1, 2, 2, 3, 5,18, 3, 1, 1, 1, // 3
         2, 3, 6, 6,-1,-1, 9, 2, 1, 1, // 4
        -1,-1,-1,-1,-1,-1, 6, 2, 1, 1, // 5
         2, 3, 6, 6,-1,-1, 9, 2, 1, 1, // 6
         1, 2, 2, 3, 5,18, 3, 1, 1, 1, // 7
         1, 1, 2, 2, 2, 2, 1, 1, 1, 1, // 8
         1, 1, 1, 1, 1, 1, 1, 1, 1, 1  // 9
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

    free(image);
    free(iterations_taken_matrix);
}

TEST_GROUP_RUNNER(fractal_should)
{
    RUN_TEST_CASE(fractal_should, calculate_complex_points_for_a_given_resolution_and_check_if_the_belong_to_the_mandelbrot_set);
}