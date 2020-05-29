#include "../lib/unity/unity.h"
#include "../lib/unity/unity_fixture.h"

#include "../../src/cycle-detection/brent.c"

TEST_GROUP(brent_algorithm_should);

TEST_SETUP(brent_algorithm_should) {}

TEST_TEAR_DOWN(brent_algorithm_should) {}

TEST(brent_algorithm_should, return_0_when_the_array_does_not_contain_any_cycle) {

    int array[20] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19};

    TEST_ASSERT_EQUAL(0, brent(array, 20));
}

TEST(brent_algorithm_should, return_1_when_the_array_contains_a_cycle_of_length_1) {

    int array_with_cycle_at_first_pos[20] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    TEST_ASSERT_EQUAL(1, brent(array_with_cycle_at_first_pos, 20));

    int array_with_cycle_not_at_first_pos[20] = {0, 1, 2, 3, 4, 5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    TEST_ASSERT_EQUAL(1, brent(array_with_cycle_not_at_first_pos, 20));
}

TEST(brent_algorithm_should, return_2_when_the_array_contains_a_cycle_of_length_2) {

    int array_with_cycle_at_first_pos[20] = {1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2};
    TEST_ASSERT_EQUAL(2, brent(array_with_cycle_at_first_pos, 20));

    int array_with_cycle_not_at_first_pos[20] = {0, 1, 2, 3, 4, 5, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2};
    TEST_ASSERT_EQUAL(2, brent(array_with_cycle_not_at_first_pos, 20));
}

TEST(brent_algorithm_should, return_3_when_the_array_contains_a_cycle_of_length_3) {

    int array[20] = {0, 1, 2, 3, 4, 5, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2};

    TEST_ASSERT_EQUAL(3, brent(array, 20));
}

TEST(brent_algorithm_should, return_4_when_the_array_contains_a_cycle_of_length_4) {

    int array[20] = {0, 1, 2, 3, 4, 5, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2};

    TEST_ASSERT_EQUAL(4, brent(array, 20));
}

TEST(brent_algorithm_should, return_5_when_the_array_contains_a_cycle_of_length_5) {

    int array[20] = {0, 1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 1, 2, 3, 4};

    TEST_ASSERT_EQUAL(5, brent(array, 20));
}

TEST_GROUP_RUNNER(brent_algorithm_should) {
    RUN_TEST_CASE(brent_algorithm_should, return_0_when_the_array_does_not_contain_any_cycle);
    RUN_TEST_CASE(brent_algorithm_should, return_1_when_the_array_contains_a_cycle_of_length_1);
    RUN_TEST_CASE(brent_algorithm_should, return_2_when_the_array_contains_a_cycle_of_length_2);
    RUN_TEST_CASE(brent_algorithm_should, return_3_when_the_array_contains_a_cycle_of_length_3);
    RUN_TEST_CASE(brent_algorithm_should, return_4_when_the_array_contains_a_cycle_of_length_4);
    RUN_TEST_CASE(brent_algorithm_should, return_5_when_the_array_contains_a_cycle_of_length_5);
}