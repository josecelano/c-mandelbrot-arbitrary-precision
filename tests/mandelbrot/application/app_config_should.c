#include "../../lib/unity/unity.h"
#include "../../lib/unity/unity_fixture.h"

#include "../../lib/helpers.h"
#include "../../lib/unity_extension.h"

#include "../../../src/mandelbrot/application/config.h"

TEST_GROUP(app_config_should);

TEST_SETUP(app_config_should) {
}

TEST_TEAR_DOWN(app_config_should) {
}

TEST(app_config_should, have_a_verbose_option_to_print_progress_enabled_by_default) {

    app_config config;
    int enabled;

    app_config_init(&config);

    enabled = app_config_verbose_option_enabled(&config, PRINT_PROGRESS);

    TEST_ASSERT_TRUE(enabled);

    app_config_clear(&config);
}

TEST(app_config_should, have_a_verbose_option_to_print_periods_disabled_by_default) {

    app_config config;
    int enabled;

    app_config_init(&config);

    enabled = app_config_verbose_option_enabled(&config, PRINT_PERIODS);

    TEST_ASSERT_FALSE(enabled);

    app_config_clear(&config);
}

TEST(app_config_should, allow_to_enable_and_disable_a_verbose_option) {

    app_config config;
    int ret;

    app_config_init(&config);

    // Enable
    app_config_enable_verbose_option(&config, PRINT_PERIODS);
    ret = app_config_verbose_option_enabled(&config, PRINT_PERIODS);
    TEST_ASSERT_EQUAL(ret, ENABLED);

    // Disable
    app_config_disable_verbose_option(&config, PRINT_PERIODS);
    ret = app_config_verbose_option_enabled(&config, PRINT_PERIODS);
    TEST_ASSERT_EQUAL(ret, DISABLED);

    app_config_clear(&config);
}

TEST_GROUP_RUNNER(app_config_should) {
    RUN_TEST_CASE(app_config_should, have_a_verbose_option_to_print_progress_enabled_by_default);
    RUN_TEST_CASE(app_config_should, have_a_verbose_option_to_print_periods_disabled_by_default);
    RUN_TEST_CASE(app_config_should, allow_to_enable_and_disable_a_verbose_option);
}