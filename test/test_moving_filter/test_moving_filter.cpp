#include "unity.h"

#include "MovingMeanFilter.hpp"
#include "MovingMinFilter.hpp"

MovingMeanFilter *mov_mean;
MovingMinFilter *mov_min;

void setUp(void)
{
    mov_mean = new MovingMeanFilter(3);
    mov_min = new MovingMinFilter(3);
}

void tearDown(void)
{
    delete mov_mean;
    delete mov_min;
}

void test_moving_mean(void)
{
    // Empty window
    TEST_ASSERT_EQUAL(0, mov_mean->calculate());

    // Partially filled window
    mov_mean->add_sample(2);
    TEST_ASSERT_EQUAL(2, mov_mean->calculate());
    mov_mean->add_sample(1);
    TEST_ASSERT_EQUAL(2, mov_mean->calculate());
    mov_mean->add_sample(1);
    TEST_ASSERT_EQUAL(1, mov_mean->calculate());

    // Window completely full, size stays at 3 samples from now.
    mov_mean->add_sample(1);
    TEST_ASSERT_EQUAL(1, mov_mean->calculate());
    mov_mean->add_sample(2);
    TEST_ASSERT_EQUAL(1, mov_mean->calculate());
    mov_mean->add_sample(2);
    TEST_ASSERT_EQUAL(2, mov_mean->calculate());
}

void test_moving_min(void)
{
    // Empty window
    TEST_ASSERT_EQUAL(0, mov_min->calculate());

    // Partially filled window
    mov_min->add_sample(50);
    TEST_ASSERT_EQUAL(50, mov_min->calculate());
    mov_min->add_sample(100);
    TEST_ASSERT_EQUAL(50, mov_min->calculate());
    mov_min->add_sample(20);
    TEST_ASSERT_EQUAL(20, mov_min->calculate());

    // Window completely full, size stays at 3 samples from now.
    mov_min->add_sample(30);
    TEST_ASSERT_EQUAL(20, mov_min->calculate());
    mov_min->add_sample(30);
    TEST_ASSERT_EQUAL(20, mov_min->calculate());
    mov_min->add_sample(30);
    TEST_ASSERT_EQUAL(30, mov_min->calculate());
}

int runUnityTests(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_moving_mean);
    RUN_TEST(test_moving_min);
    return UNITY_END();
}

int main(void)
{
    return runUnityTests();
}
