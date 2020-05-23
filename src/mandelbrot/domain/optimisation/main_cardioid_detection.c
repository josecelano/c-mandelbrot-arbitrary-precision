#include "arb.h"
#include "acb.h"

#include "main_cardioid_detection.h"

int inside_main_cardioid(acb_t c, app_config config) {
    int ret = 0;
    arb_t x, y;           // Real and imaginary parts
    arb_t a, b;           // Left and right side of the comparison operation
    arb_t q;              // Variable in the formula
    arb_t temp;           // Temporal results and constants in the formula
    arb_t _x_minus_0_25;  // x - 1/4
    arb_t _0_25;          // 1/4
    arb_t y_sqr;          // y²

    arb_init(x);
    arb_init(y);

    arb_init(a);
    arb_init(b);

    arb_init(q);

    arb_init(temp);
    arb_init(_x_minus_0_25);
    arb_init(_0_25);
    arb_init(y_sqr);

    // Set formula constants
    arb_set_str(_0_25, "0.25", config.precision);

    // Get real and imaginary parts
    acb_get_real(x, c);
    acb_get_imag(y, c);

    /**  Calculate variable q **/

    // _x_minus_0_25 = x - 1/4
    arb_sub(_x_minus_0_25, x, _0_25, config.precision);
    // temp = (x - 1/4)²
    arb_sqr(temp, _x_minus_0_25, config.precision);
    // y²
    arb_sqr(y_sqr, y, config.precision);

    // q = (x - 1/4)² + y²
    arb_add(q, temp, y_sqr, config.precision);

    /**  Calculate a (left side of comparison) **/

    // temp = q + (x - 1/4)
    arb_add(temp, q, _x_minus_0_25, config.precision);
    // a = q * (q + (x - 1/4))
    arb_mul(a, q, temp, config.precision);

    /**  Calculate b (right side of comparison) **/

    // b = 1/4 * y²
    arb_mul(b, _0_25, y_sqr, config.precision);

    // a < b
    if (arb_lt(a, b)) {
        ret = 1;
    }

    arb_clear(x);
    arb_clear(y);

    arb_clear(a);
    arb_clear(b);

    arb_clear(q);

    arb_clear(temp);
    arb_clear(_x_minus_0_25);
    arb_clear(_0_25);
    arb_clear(y_sqr);

    return ret;
}