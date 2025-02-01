#include "unity.h"

void setUp(void) {}

void tearDown(void) {}

void test_that_unit_testing_works(void) {}

int runUnityTests(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_that_unit_testing_works);
    return UNITY_END();
}

int main(void)
{
    return runUnityTests();
}
