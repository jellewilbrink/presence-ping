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

void test_is_apple_find_my_service(void)
{
    const std::string apple_id = "4c00";
    const std::string find_my_service_id = "12";

    const std::string other_id = "0000";
    const std::string other_service_id = "11";
    const std::string more_hex_string = "89AB";

    // Minimal manufacturer data string
    TEST_ASSERT(ble_scanner_utils->is_apple_find_my_service(apple_id + find_my_service_id));

    // Longer manufacturer data string
    TEST_ASSERT(ble_scanner_utils->is_apple_find_my_service(apple_id + find_my_service_id + more_hex_string));

    // Too short
    TEST_ASSERT_FALSE(ble_scanner_utils->is_apple_find_my_service(apple_id));

    // Wrong manufacturer ID
    TEST_ASSERT_FALSE(ble_scanner_utils->is_apple_find_my_service(other_id + find_my_service_id));

    // Wrong service ID
    TEST_ASSERT_FALSE(ble_scanner_utils->is_apple_find_my_service(apple_id + other_service_id));
}

int runUnityTests(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_parse_manufacturer_id);
    RUN_TEST(test_parse_manufacturer_id_temp_object);
    RUN_TEST(test_is_apple_find_my_service);
    return UNITY_END();
}

int main(void)
{
    return runUnityTests();
}
