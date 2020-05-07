#include "../external/unity/unity_fixture.h"

static void RunAllTests(void)
{
    RUN_TEST_GROUP(fractal_should);
    RUN_TEST_GROUP(formula_should);
    RUN_TEST_GROUP(set_should);
}

int main(int argc, const char *argv[]) {
    return UnityMain(argc, argv, RunAllTests);
}