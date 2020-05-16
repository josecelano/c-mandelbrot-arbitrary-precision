#ifndef C_MANDELBROT_ARBITRARY_PRECISION_UNITY_EXTENSION_H
#define C_MANDELBROT_ARBITRARY_PRECISION_UNITY_EXTENSION_H

/*-------------------------------------------------------
 * Test Asserts for complex numbers
 *-------------------------------------------------------*/

#define TEST_ASSERT_COMPLEX_EQUALS(expected, actual)   TEST_ASSERT_TRUE_MESSAGE(acb_equal(expected_result, result), "complex numbers are not equal")

#endif //C_MANDELBROT_ARBITRARY_PRECISION_UNITY_EXTENSION_H
