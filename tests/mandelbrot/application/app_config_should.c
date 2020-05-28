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

    config_t config;
    int enabled;

    app_config_init(&config);

    enabled = app_config_verbose_option_enabled(config, VO_PRINT_PROGRESS);

    TEST_ASSERT_TRUE(enabled);
}

TEST(app_config_should, have_a_verbose_option_to_print_periods_disabled_by_default) {

    config_t config;
    int enabled;

    app_config_init(&config);

    enabled = app_config_verbose_option_enabled(config, VO_PRINT_PERIODS);

    TEST_ASSERT_FALSE(enabled);
}

TEST(app_config_should, allow_to_enable_and_disable_a_verbose_option) {

    config_t config;
    int ret;

    app_config_init(&config);

    // Enable
    app_config_enable_verbose_option(&config, VO_PRINT_PERIODS);
    ret = app_config_verbose_option_enabled(config, VO_PRINT_PERIODS);
    TEST_ASSERT_EQUAL(ret, ENABLED);

    // Disable
    app_config_disable_verbose_option(&config, VO_PRINT_PERIODS);
    ret = app_config_verbose_option_enabled(config, VO_PRINT_PERIODS);
    TEST_ASSERT_EQUAL(ret, DISABLED);
}

TEST_GROUP_RUNNER(app_config_should) {
    RUN_TEST_CASE(app_config_should, have_a_verbose_option_to_print_progress_enabled_by_default);
    RUN_TEST_CASE(app_config_should, have_a_verbose_option_to_print_periods_disabled_by_default);
    RUN_TEST_CASE(app_config_should, allow_to_enable_and_disable_a_verbose_option);
}