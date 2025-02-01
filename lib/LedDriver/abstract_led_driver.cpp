#include "abstract_led_driver.hpp"

AbstractLedDriver::AbstractLedDriver()
{
    number_of_initialized_pins = 0;
    initialized_led_pins.fill(0xFF);
}

void AbstractLedDriver::init_led(uint8_t pin)
{
    // A Led pin can only be initialized once
    if (is_led_pin_initialized(pin))
        return;
    // No size in the array to initialize another pin
    if (number_of_initialized_pins >= initialized_led_pins.size())
        return;

    set_pin_mode(pin, OUTPUT);
    set_pin_state(pin, LOW);

    initialized_led_pins[number_of_initialized_pins] = pin;
    number_of_initialized_pins++;
}

bool AbstractLedDriver::set_pin_high(uint8_t pin)
{
    if (is_led_pin_initialized(pin))
    {
        set_pin_state(pin, HIGH);
        return true;
    }
    return false;
}

bool AbstractLedDriver::set_pin_low(uint8_t pin)
{
    if (is_led_pin_initialized(pin))
    {
        set_pin_state(pin, LOW);
        return true;
    }
    return false;
    return true;
}

bool AbstractLedDriver::is_led_pin_initialized(uint8_t pin)
{
    if (pin == 0xFF)
        return false;

    bool found = false;
    for (const uint8_t &initialized_pin : initialized_led_pins)
    {
        if (initialized_pin == pin)
        {
            found = true;
        }
    }
    return found;
}
