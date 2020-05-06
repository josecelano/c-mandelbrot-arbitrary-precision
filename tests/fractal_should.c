#include "../external/unity/unity.h"
#include "../external/unity/unity_fixture.h"
#include "../tests/unity_extension.h"
#include "../src/fractal.h"

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
    int res_x = 10, res_y = 10;
    int max_iterations = 200;
    char* image;
    int *iterations_taken_matrix;
    FILE *fp;
    int x, y;
    char message[100];

    image = malloc(res_x * res_y * 3);
    iterations_taken_matrix = malloc(res_x * res_y * sizeof *iterations_taken_matrix);

    calculate_points(res_x, res_y, max_iterations, prec, iterations_taken_matrix);

    int expected_iterations_taken_matrix[100] = {
    // x 0, 1, 2, 3, 4, 5, 6, 7, 8, 9  // y
         2, 2, 2, 2, 2, 2, 2, 2, 2, 2, // 0
         2, 2, 2, 2, 2, 2, 2, 2, 2, 2, // 1
         2, 2, 3, 3, 3, 3, 2, 2, 2, 2, // 2
         2, 3, 3, 4, 6,19, 4, 2, 2, 2, // 3
         3, 4, 7, 7,-1,-1,10, 3, 2, 2, // 4
        -1,-1,-1,-1,-1,-1, 7, 3, 2, 2, // 5
         3, 4, 7, 7,-1,-1,10, 3, 2, 2, // 6
         2, 3, 3, 4, 6,19, 4, 2, 2, 2, // 7
         2, 2, 3, 3, 3, 3, 2, 2, 2, 2, // 8
         2, 2, 2, 2, 2, 2, 2, 2, 2, 2  // 9
    };

    for (y = 0; y < res_y; y++) {
        for (x = 0; x < res_x; x++) {
            sprintf(message, "expected number of iterations %d does not match actual %d for pixel (x,y) = (%d, %d)",
                    expected_iterations_taken_matrix[(y * res_x) + x],
                    iterations_taken_matrix[(y * res_x) + x],
                    x, y
                    );

            TEST_ASSERT_EQUAL_MESSAGE(expected_iterations_taken_matrix[(y * res_x) + x], iterations_taken_matrix[(y * res_x) + x], message);
        }
    }

    free(image);
    free(iterations_taken_matrix);
}

TEST_GROUP_RUNNER(fractal_should)
{
    RUN_TEST_CASE(fractal_should, calculate_complex_points_for_a_given_resolution_and_check_if_the_belong_to_the_mandelbrot_set);
}