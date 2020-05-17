#include "../lib/unity/unity.h"
#include "../lib/unity/unity_fixture.h"
#include "../lib/unity_extension.h"

#include "../../src/mandelbrot/domain/formula.h"
#include "../../src/mandelbrot/domain/complex.h"

TEST_GROUP(formula_should);

TEST_SETUP(formula_should)
{
}

TEST_TEAR_DOWN(formula_should)
{
}

TEST(formula_should, calculate_the_mandelbrot_function)
{
    slong prec = 128;
    acb_t z, c, result, expected_result;
    int i;

    acb_init(z);
    acb_init(c);
    acb_init(result);
    acb_init(expected_result);

    // Some formula values to test
    // z,c,expected_result
    complex_dto zf[9][3] = {
            // With z=0 -> return c
            // z=0 c=0 -> z² + c = 0
            {{ "0", "0" }, { "0", "0" }, { "0", "0" }},
            // z=0 c=1 -> z² + c = 1
            {{ "0", "0" }, { "1", "0" }, { "1", "0" }},
            // z=0 c=i -> z² + c = i
            {{ "0", "0" }, { "0", "1" }, { "0", "1" }},

            // With z=1 -> return 1 + c
            // z=1 c=0 -> z² + c = 0
            {{ "1", "0" }, { "0", "0" }, { "1", "0" }},
            // z=1 c=1 -> z² + c = 1
            {{ "1", "0" }, { "1", "0" }, { "2", "0" }},
            // z=1 c=i -> z² + c = i
            {{ "1", "0" }, { "0", "1" }, { "1", "1" }},

            // With z=i -> return -1 + c
            // z=i c=0 -> z² + c = i² + 0 = -1
            {{ "0", "1" }, { "0", "0" }, { "-1", "0" }},
            // z=i c=1 -> z² + c = i² + 1 = 0
            {{ "0", "1" }, { "1", "0" }, { "0", "0" }},
            // z=i c=i -> z² + c = i² + i = -1 + i
            {{ "0", "1" }, { "0", "1" }, { "-1", "1" }}
    };

    for (i = 0; i < 9; ++i)
    {
        complex_set_from_re_im_str(z, zf[i][0].re, zf[i][0].im, prec);
        complex_set_from_re_im_str(c, zf[i][1].re, zf[i][1].im, prec);
        complex_set_from_re_im_str(expected_result, zf[i][2].re, zf[i][2].im, prec);

        mandelbrot_formula(result, z, c, prec);

        TEST_ASSERT_COMPLEX_EQUALS(expected_result, result);
    }

    acb_clear(z);
    acb_clear(c);
    acb_clear(result);
    acb_clear(expected_result);
}

TEST_GROUP_RUNNER(formula_should)
{
    RUN_TEST_CASE(formula_should, calculate_the_mandelbrot_function);
}