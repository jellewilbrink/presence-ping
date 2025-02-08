#include "unity.h"
#include "ble_scanner_utils.hpp"

BleScannerUtils *ble_scanner_utils;

void setUp(void)
{
    ble_scanner_utils = new BleScannerUtils();
}

void tearDown(void)
{
    delete ble_scanner_utils;
}

void test_parse_manufacturer_id(void)
{
    TEST_ASSERT_EQUAL(0x1234, ble_scanner_utils->parse_manufacturer_id("1234567890ABCDEF"));
}

void test_parse_manufacturer_id_temp_object(void)
{
    TEST_ASSERT_EQUAL(0x1234, BleScannerUtils().parse_manufacturer_id("1234567890ABCDEF"));
}

int runUnityTests(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_parse_manufacturer_id);
    RUN_TEST(test_parse_manufacturer_id_temp_object);
    return UNITY_END();
}

int main(void)
{
    return runUnityTests();
}
