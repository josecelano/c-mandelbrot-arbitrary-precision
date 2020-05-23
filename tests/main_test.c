#include "./lib/unity/unity_fixture.h"

static void RunAllTests(void)
{
    // Unit tests
    RUN_TEST_GROUP(fractal_should);
    RUN_TEST_GROUP(formula_should);
    RUN_TEST_GROUP(image_should);
    RUN_TEST_GROUP(mandelbrot_set_should);
    RUN_TEST_GROUP(app_config_should);

    // Integration tests
    RUN_TEST_GROUP(ascii_graph_should);
}

int main(int argc, const char *argv[]) {
    return UnityMain(argc, argv, RunAllTests);
}