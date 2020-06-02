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

TEST(app_config_should, allow_to_enable_and_disable_a_verbose_option) {

    config_t config;
    int ret;

    app_config_init(&config);

    // Enable
    app_config_enable_verbose_option(&config, VO_PRINT_PERIODS);
    ret = app_config_verbose_option_enabled(&config, VO_PRINT_PERIODS);
    TEST_ASSERT_TRUE(ret);

    // Disable
    app_config_disable_verbose_option(&config, VO_PRINT_PERIODS);
    ret = app_config_verbose_option_enabled(&config, VO_PRINT_PERIODS);
    TEST_ASSERT_FALSE(ret);
}

TEST(app_config_should, have_a_verbose_option_to_print_progress_disabled_by_default) {

    config_t config;
    int enabled;

    app_config_init(&config);

    enabled = app_config_verbose_option_enabled(&config, VO_PRINT_PROGRESS);

    TEST_ASSERT_FALSE(enabled);
}

TEST(app_config_should, have_a_verbose_option_to_print_periods_disabled_by_default) {

    config_t config;
    int enabled;

    app_config_init(&config);

    enabled = app_config_verbose_option_enabled(&config, VO_PRINT_PERIODS);

    TEST_ASSERT_FALSE(enabled);
}

TEST(app_config_should, allow_to_enable_and_disable_a_optimisation_option) {

    config_t config;
    int ret;

    app_config_init(&config);

    // Enable
    app_config_enable_optimisation_option(&config, OO_MAIN_CARDIOID_DETECTION);
    ret = app_config_optimisation_option_enabled(&config, OO_MAIN_CARDIOID_DETECTION);
    TEST_ASSERT_TRUE(ret);

    // Disable
    app_config_disable_optimisation_option(&config, OO_MAIN_CARDIOID_DETECTION);
    ret = app_config_optimisation_option_enabled(&config, OO_MAIN_CARDIOID_DETECTION);
    TEST_ASSERT_FALSE(ret);
}

TEST(app_config_should, have_a_optimisation_option_to_use_main_cardioid_detection_disabled_by_default) {

    config_t config;
    int enabled;

    app_config_init(&config);

    enabled = app_config_optimisation_option_enabled(&config, OO_MAIN_CARDIOID_DETECTION);

    TEST_ASSERT_FALSE(enabled);
}

TEST(app_config_should, have_a_optimisation_option_to_use_period2_detection_disabled_by_default) {

    config_t config;
    int enabled;

    app_config_init(&config);

    enabled = app_config_optimisation_option_enabled(&config, OO_PERIOD2_DETECTION);

    TEST_ASSERT_FALSE(enabled);
}

TEST(app_config_should, have_a_optimisation_option_to_use_periodicity_checking_disabled_by_default) {

    config_t config;
    int enabled;

    app_config_init(&config);

    enabled = app_config_optimisation_option_enabled(&config, OO_PERIODICITY_CHECKING);

    TEST_ASSERT_FALSE(enabled);
}

TEST_GROUP_RUNNER(app_config_should) {
    // Verbose options
    RUN_TEST_CASE(app_config_should, allow_to_enable_and_disable_a_verbose_option);
    RUN_TEST_CASE(app_config_should, have_a_verbose_option_to_print_progress_disabled_by_default);
    RUN_TEST_CASE(app_config_should, have_a_verbose_option_to_print_periods_disabled_by_default);
    // Optimisation options
    RUN_TEST_CASE(app_config_should, allow_to_enable_and_disable_a_optimisation_option);
    RUN_TEST_CASE(app_config_should, have_a_optimisation_option_to_use_main_cardioid_detection_disabled_by_default);
    RUN_TEST_CASE(app_config_should, have_a_optimisation_option_to_use_period2_detection_disabled_by_default);
    RUN_TEST_CASE(app_config_should, have_a_optimisation_option_to_use_periodicity_checking_disabled_by_default);
}