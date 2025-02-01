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

// 0xFF is the special case for unitiliazed list values, so should return false.
void test_is_led_pin_initialized_0xff()
{
    bool result = led_driver_mock->is_led_pin_initialized(0xFF);
    TEST_ASSERT_EQUAL(false, result);
}

void test_is_led_pin_initialized_false()
{
    uint8_t pin = 1;
    uint8_t other_pin = 2;

    led_driver_mock->init_led(pin);
    bool result = led_driver_mock->is_led_pin_initialized(other_pin);

    TEST_ASSERT_EQUAL(false, result);
}

void test_is_led_pin_initialized_true()
{
    uint8_t pin = 1;

    led_driver_mock->init_led(pin);
    bool result = led_driver_mock->is_led_pin_initialized(pin);

    TEST_ASSERT_EQUAL(true, result);
}

void test_is_led_pin_initialized_true_multiple()
{
    uint8_t pin = 1;
    uint8_t pin2 = 2;

    TEST_ASSERT_EQUAL(false, led_driver_mock->is_led_pin_initialized(pin));
    TEST_ASSERT_EQUAL(false, led_driver_mock->is_led_pin_initialized(pin2));
    led_driver_mock->init_led(pin);
    led_driver_mock->init_led(pin2);
    TEST_ASSERT_EQUAL(true, led_driver_mock->is_led_pin_initialized(pin2));
    TEST_ASSERT_EQUAL(true, led_driver_mock->is_led_pin_initialized(pin));
}

void test_too_init_too_many_pins()
{
    // This test assumes array initialized_led_pins has lenght 2
    TEST_ASSERT_EQUAL(2, MAX_NUMBER_OF_LED_PINS);

    // If too many pins are initialized, new pins inits should be ignored.
    uint8_t pin = 1;
    uint8_t pin2 = 2;
    uint8_t pin3 = 3;

    TEST_ASSERT_EQUAL(false, led_driver_mock->is_led_pin_initialized(pin));
    TEST_ASSERT_EQUAL(false, led_driver_mock->is_led_pin_initialized(pin2));
    TEST_ASSERT_EQUAL(false, led_driver_mock->is_led_pin_initialized(pin3));

    led_driver_mock->init_led(pin);
    led_driver_mock->init_led(pin2);
    led_driver_mock->init_led(pin3);

    TEST_ASSERT_EQUAL(false, led_driver_mock->is_led_pin_initialized(pin3)); // ignored
    TEST_ASSERT_EQUAL(true, led_driver_mock->is_led_pin_initialized(pin2));
    TEST_ASSERT_EQUAL(true, led_driver_mock->is_led_pin_initialized(pin));
}

void test_pin_init_multiple_times_but_only_once_in_list()
{
    // This test assumes array initialized_led_pins has lenght 2
    TEST_ASSERT_EQUAL(2, MAX_NUMBER_OF_LED_PINS);

    uint8_t pin = 1;
    uint8_t pin2 = 2;

    // Initialize pin 1 multiple times
    led_driver_mock->init_led(pin);
    led_driver_mock->init_led(pin);
    TEST_ASSERT_EQUAL(1, led_driver_mock->number_set_pin_mode_called);
    TEST_ASSERT_EQUAL(1, led_driver_mock->number_set_pin_state_called);

    // Pin 1 should only be in the list once, so there should be place for pin 2
    led_driver_mock->init_led(pin2);
    TEST_ASSERT_EQUAL(2, led_driver_mock->number_set_pin_mode_called);
    TEST_ASSERT_EQUAL(2, led_driver_mock->number_set_pin_state_called);
    TEST_ASSERT_EQUAL(true, led_driver_mock->is_led_pin_initialized(pin2));
}

void test_set_pin_high()
{
    led_driver_mock->init_led(1);
    bool result = led_driver_mock->set_pin_high(1);

    TEST_ASSERT_EQUAL(true, result);
    TEST_ASSERT_EQUAL(1, led_driver_mock->number_set_pin_mode_called);
    TEST_ASSERT_EQUAL(2, led_driver_mock->number_set_pin_state_called);
}

void test_set_pin_low()
{
    led_driver_mock->init_led(1);
    bool result = led_driver_mock->set_pin_low(1);

    TEST_ASSERT_EQUAL(true, result);
    TEST_ASSERT_EQUAL(1, led_driver_mock->number_set_pin_mode_called);
    TEST_ASSERT_EQUAL(2, led_driver_mock->number_set_pin_state_called);
}

// Keep track of initialized pins
void test_drive_uninitialized_pin_high(void)
{
    TEST_ASSERT_EQUAL(false, led_driver_mock->set_pin_high(1));
    TEST_ASSERT_EQUAL(0, led_driver_mock->number_set_pin_mode_called);
    TEST_ASSERT_EQUAL(0, led_driver_mock->number_set_pin_state_called);
}

// Keep track of initialized pins
void test_drive_uninitialized_pin_low(void)
{
    TEST_ASSERT_EQUAL(false, led_driver_mock->set_pin_low(1));
    TEST_ASSERT_EQUAL(0, led_driver_mock->number_set_pin_mode_called);
    TEST_ASSERT_EQUAL(0, led_driver_mock->number_set_pin_state_called);
}

int runUnityTests(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_init_calls_set_pin_mode_and_state);
    RUN_TEST(test_is_led_pin_initialized_0xff);
    RUN_TEST(test_is_led_pin_initialized_false);
    RUN_TEST(test_is_led_pin_initialized_true);
    RUN_TEST(test_is_led_pin_initialized_true_multiple);
    RUN_TEST(test_too_init_too_many_pins);
    RUN_TEST(test_pin_init_multiple_times_but_only_once_in_list);
    RUN_TEST(test_set_pin_high);
    RUN_TEST(test_set_pin_low);
    RUN_TEST(test_drive_uninitialized_pin_high);
    RUN_TEST(test_drive_uninitialized_pin_low);
    return UNITY_END();
}

int main(void)
{
    return runUnityTests();
}
