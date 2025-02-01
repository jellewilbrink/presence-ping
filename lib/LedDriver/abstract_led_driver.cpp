#include "abstract_led_driver.hpp"

void AbstractLedDriver::init_led(uint8_t pin)
{
    set_pin_mode(pin, OUTPUT);
    set_pin_state(pin, LOW);
}

bool AbstractLedDriver::set_pin_high(uint8_t pin)
{
    set_pin_state(pin, HIGH);
    return true;
}

bool AbstractLedDriver::set_pin_low(uint8_t pin)
{
    set_pin_state(pin, LOW);
    return true;
}
