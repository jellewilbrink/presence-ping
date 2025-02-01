#include "unity.h"

#include "abstract_led_driver.hpp"

class LedDriverMock : public AbstractLedDriver
{
public:
    LedDriverMock()
    {
        number_set_pin_mode_called = 0;
        number_set_pin_state_called = 0;
    }

    int number_set_pin_mode_called;
    int number_set_pin_state_called;

protected:
    void set_pin_mode(uint8_t pin, uint8_t mode) { number_set_pin_mode_called++; };
    void set_pin_state(uint8_t pin, uint8_t val) { number_set_pin_state_called++; };
};

LedDriverMock *led_driver_mock;

void setUp(void)
{
    led_driver_mock = new LedDriverMock();
}

void tearDown(void)
{
    delete led_driver_mock;
}

void test_init_calls_set_pin_mode_and_state(void)
{
    led_driver_mock->init_led(1);
    TEST_ASSERT_EQUAL(1, led_driver_mock->number_set_pin_mode_called);
    TEST_ASSERT_EQUAL(1, led_driver_mock->number_set_pin_state_called);

    // Initialize another pin
    led_driver_mock->init_led(3);
    TEST_ASSERT_EQUAL(2, led_driver_mock->number_set_pin_mode_called);
    TEST_ASSERT_EQUAL(2, led_driver_mock->number_set_pin_state_called);
}

// Keep track of initialized pins
// test_drive_initialized_pin
// test_drive_uninitialized_pin

int runUnityTests(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_init_calls_set_pin_mode_and_state);
    return UNITY_END();
}

int main(void)
{
    return runUnityTests();
}
