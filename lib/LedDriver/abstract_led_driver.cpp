#include "abstract_led_driver.hpp"

void AbstractLedDriver::init_led(uint8_t pin)
{
    set_pin_mode(pin, OUTPUT);
    set_pin_state(pin, LOW);
}