#include "unity.h"

void setUp(void) {}

void tearDown(void) {}

void test_nothing(void) {}

int runUnityTests(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_nothing);
    return UNITY_END();
}

int main(void)
{
    return runUnityTests();
}
