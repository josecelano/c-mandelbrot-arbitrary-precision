#include <stdio.h>
#include "../lib/unity/unity.h"
#include "../lib/unity/unity_fixture.h"

#include "../../src/mandelbrot/domain/complex.h"
#include "../../src/mandelbrot/domain/set.h"
#include "../../src/mandelbrot/domain/zpoint.h"

TEST_GROUP(mandelbrot_set_should);

TEST_SETUP(mandelbrot_set_should)
{
}

TEST_TEAR_DOWN(mandelbrot_set_should)
{
}

TEST(mandelbrot_set_should, contain_known_points_inside)
{
    const int max_iterations = 200;
    int i, ret;
    slong prec = 32;
    zpoint point;
    char message[100];

    zpoint_init(&point);

    // Some complex number inside the Mandelbrot Set
    complex_dto z_in[6] = {
            { "0", "0" },
            { "-1", "0" },
            { "-0.5", "0" },
            { "-0.5", "0.5" },
            { "-2", "0" },
            { "4.25e-8", "4.25e-8" }
    };

    for (i = 0; i < 6; ++i)
    {
        zpoint_set_from_complex_dto(&point, z_in[i], prec);

        ret = mandelbrot_set_contains(point, max_iterations, prec);

        sprintf(message, "complex number (%s,%s) in test case #%d should be in Mandelbrot Set", z_in[i].re, z_in[i].im, i);

        TEST_ASSERT_EQUAL_MESSAGE(INSIDE, ret, message);
    }

    zpoint_clean(&point);
}

TEST(mandelbrot_set_should, not_contain_known_points_outside)
{
    slong prec = 32;
    int i, ret, max_iterations = 200;
    zpoint point;
    char message[100];

    zpoint_init(&point);

    // Some complex number inside the Mandelbrot Set
    complex_dto z_out[6] = {
            { "-2", "2" },
            { "0", "2" },
            { "2", "2" },
            { "0", "2" },
            { "0", "-2" },
            { "-2", "-2" }
    };

    for (i = 0; i < 6; ++i)
    {
        zpoint_set_from_complex_dto(&point, z_out[i], prec);

        ret = mandelbrot_set_contains(point, max_iterations, prec);

        sprintf(message, "complex number (%s,%s) in test case #%d should not be in Mandelbrot Set", z_out[i].re, z_out[i].im, i);

        TEST_ASSERT_EQUAL_MESSAGE(OUTSIDE, ret, message);
    }

    zpoint_clean(&point);
}

TEST(mandelbrot_set_should, check_if_point_is_inside_main_cardioid_in_order_to_increase_performace)
{
    slong prec = 32;
    acb_t c;
    int i, ret;
    char message[100];

    acb_init(c);

    // Some complex number inside the main cardioid
    complex_dto z_in[5] = {
            { "0", "0" },
            { "-0.6", "0" },
            { "0.2", "0" },
            { "0", "0.5" },
            { "0", "-0.5" }
    };

    for (i = 0; i < 5; ++i)
    {
        complex_set_from_complex_dto(c, z_in[i], prec);

        ret = inside_main_cardioid(c, prec);

        sprintf(message, "complex number (%s,%s) in test case #%d is not inside the main cardioid", z_in[i].re, z_in[i].im, i);

        TEST_ASSERT_TRUE_MESSAGE(ret, message);
    }

    // Some complex number outside the main cardioid
    complex_dto z_out[5] = {
            { "0.3", "0" },
            { "-2", "0" },
            { "0", "0.7" },
            { "0", "-0.7" },
            { "2", "2" }
    };

    for (i = 0; i < 5; ++i)
    {
        complex_set_from_complex_dto(c, z_out[i], prec);

        ret = inside_main_cardioid(c, prec);

        sprintf(message, "complex number (%s,%s) in test case #%d is not outside the main cardioid", z_out[i].re, z_out[i].im, i);

        TEST_ASSERT_FALSE_MESSAGE(ret, message);
    }

    acb_clear(c);
}

TEST(mandelbrot_set_should, check_if_point_is_inside_period_2_bulb_in_order_to_increase_performace)
{
    slong prec = 32;
    acb_t c;
    int i, ret;
    char message[100];

    acb_init(c);

    // Some complex number inside the period-2 bulb (big circle on the left of the main cardioid)
    complex_dto z_in[5] = {
            { "-1", "0" },
            { "-1.1", "0.1" },
            { "-0.9", "0.1" },
            { "-1.1", "-0.1" },
            { "-0.9", "-0.1" }
    };

    for (i = 0; i < 5; ++i)
    {
        complex_set_from_complex_dto(c, z_in[i], prec);

        ret = inside_period_2_bulb(c, prec);

        sprintf(message, "complex number (%s,%s) in test case #%d is not inside the period-2 bulb", z_in[i].re, z_in[i].im, i);

        TEST_ASSERT_TRUE_MESSAGE(ret, message);
    }

    // Some complex number outside the period-2 bulb
    complex_dto z_out[5] = {
            { "0.3", "0" },
            { "-2", "0" },
            { "0", "0.7" },
            { "0", "-0.7" },
            { "2", "2" }
    };

    for (i = 0; i < 5; ++i)
    {
        complex_set_from_complex_dto(c, z_out[i], prec);

        ret = inside_period_2_bulb(c, prec);

        sprintf(message, "complex number (%s,%s) in test case #%d is not outside the period-2 bulb", z_out[i].re, z_out[i].im, i);

        TEST_ASSERT_FALSE_MESSAGE(ret, message);
    }

    acb_clear(c);
}

TEST_GROUP_RUNNER(mandelbrot_set_should)
{
    RUN_TEST_CASE(mandelbrot_set_should, contain_known_points_inside);
    RUN_TEST_CASE(mandelbrot_set_should, not_contain_known_points_outside);
    RUN_TEST_CASE(mandelbrot_set_should, check_if_point_is_inside_main_cardioid_in_order_to_increase_performace);
    RUN_TEST_CASE(mandelbrot_set_should, check_if_point_is_inside_period_2_bulb_in_order_to_increase_performace);
}