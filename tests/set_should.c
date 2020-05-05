#include <stdio.h>
#include "../external/unity/unity.h"
#include "../external/unity/unity_fixture.h"
#include "../src/complex.h"
#include "../src/set.h"

TEST_GROUP(set_should);

TEST_SETUP(set_should)
{
}

TEST_TEAR_DOWN(set_should)
{
}

TEST(set_should, contain_known_points_inside)
{
    const int max_iterations = 200;
    int i, ret;
    slong prec = 32;
    acb_t c;
    char message[100];

    acb_init(c);

    // Some complex number inside the Mandelbrot Set
    struct complex_dto z_in[6] = {
            { "0", "0" },
            { "-1", "0" },
            { "-0.5", "0" },
            { "-0.5", "0.5" },
            { "-2", "0" },
            { "4.25e-8", "4.25e-8" }
    };

    for (i = 0; i < 6; ++i)
    {
        complex_set_from_str(c, z_in[i].re, z_in[i].im, prec);

        ret = mandelbrot_set_contains(c, max_iterations, prec);

        sprintf(message, "complex number (%s,%s) in test case #%d should be in Mandelbrot Set", z_in[i].re, z_in[i].im, i);

        TEST_ASSERT_EQUAL_MESSAGE(-1, ret, message);
    }

    acb_clear(c);
}

TEST(set_should, not_contain_known_points_outside)
{
    slong prec = 32;
    int i, ret, max_iterations = 200;
    acb_t c;
    char message[100];

    acb_init(c);

    // Some complex number inside the Mandelbrot Set
    struct complex_dto z_out[7] = {
            { "-2", "2" },
            { "0", "2" },
            { "2", "2" },
            { "0", "2" },
            { "0", "-2" },
            { "-2", "-2" }
    };

    for (i = 0; i < 7; ++i)
    {
        complex_set_from_str(c, z_out[i].re, z_out[i].im, prec);

        ret = mandelbrot_set_contains(c, max_iterations, prec);

        sprintf(message, "complex number (%s,%s) in test case #%d should not be in Mandelbrot Set", z_out[i].re, z_out[i].im, i);

        TEST_ASSERT_NOT_EQUAL_MESSAGE(-1, ret, message);
    }

    acb_clear(c);
}

TEST_GROUP_RUNNER(set_should)
{
    RUN_TEST_CASE(set_should, contain_known_points_inside);
    RUN_TEST_CASE(set_should, not_contain_known_points_outside);
}