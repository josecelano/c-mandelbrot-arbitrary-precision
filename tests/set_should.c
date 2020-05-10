#include <stdio.h>
#include "../external/unity/unity.h"
#include "../external/unity/unity_fixture.h"
#include "../src/mandelbrot/complex.h"
#include "../src/mandelbrot/set.h"
#include "../src/mandelbrot/zpoint.h"

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
    zpoint point;
    char message[100];

    zpoint_init(&point);

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
        zpoint_set_from_re_im_str(&point, z_in[i].re, z_in[i].im, prec);

        ret = mandelbrot_set_contains(point, max_iterations, prec);

        sprintf(message, "complex number (%s,%s) in test case #%d should be in Mandelbrot Set", z_in[i].re, z_in[i].im, i);

        TEST_ASSERT_EQUAL_MESSAGE(-1, ret, message);
    }

    zpoint_clean(&point);
}

TEST(set_should, not_contain_known_points_outside)
{
    slong prec = 32;
    int i, ret, max_iterations = 200;
    zpoint point;
    char message[100];

    zpoint_init(&point);

    // Some complex number inside the Mandelbrot Set
    struct complex_dto z_out[6] = {
            { "-2", "2" },
            { "0", "2" },
            { "2", "2" },
            { "0", "2" },
            { "0", "-2" },
            { "-2", "-2" }
    };

    for (i = 0; i < 6; ++i)
    {
        zpoint_set_from_re_im_str(&point, z_out[i].re, z_out[i].im, prec);

        ret = mandelbrot_set_contains(point, max_iterations, prec);

        sprintf(message, "complex number (%s,%s) in test case #%d should not be in Mandelbrot Set", z_out[i].re, z_out[i].im, i);

        TEST_ASSERT_NOT_EQUAL_MESSAGE(-1, ret, message);
    }

    zpoint_clean(&point);
}

TEST(set_should, check_if_point_is_inside_main_cardioid_in_order_to_increase_performace)
{
    slong prec = 32;
    acb_t c;
    int i, ret;
    char message[100];

    acb_init(c);

    // Some complex number inside the main cardioid

    struct complex_dto z_in[5] = {
            { "0", "0" },
            { "-0.6", "0" },
            { "0.2", "0" },
            { "0", "0.5" },
            { "0", "-0.5" }
    };

    for (i = 0; i < 5; ++i)
    {
        complex_set_from_re_im_str(c, z_in[i].re, z_in[i].im, prec);

        ret = inside_main_cardioid(c, prec);

        sprintf(message, "complex number (%s,%s) in test case #%d is not inside the main cardioid", z_in[i].re, z_in[i].im, i);

        TEST_ASSERT_TRUE_MESSAGE(ret, message);
    }

    // Some complex number outside the main cardioid

    struct complex_dto z_out[5] = {
            { "0.3", "0" },
            { "-2", "0" },
            { "0", "0.7" },
            { "0", "-0.7" },
            { "2", "2" }
    };

    for (i = 0; i < 5; ++i)
    {
        complex_set_from_re_im_str(c, z_out[i].re, z_out[i].im, prec);

        ret = inside_main_cardioid(c, prec);

        sprintf(message, "complex number (%s,%s) in test case #%d is not outside the main cardioid", z_out[i].re, z_out[i].im, i);

        TEST_ASSERT_FALSE_MESSAGE(ret, message);
    }

    acb_clear(c);
}

TEST_GROUP_RUNNER(set_should)
{
    RUN_TEST_CASE(set_should, contain_known_points_inside);
    RUN_TEST_CASE(set_should, not_contain_known_points_outside);
    RUN_TEST_CASE(set_should, check_if_point_is_inside_main_cardioid_in_order_to_increase_performace);
}