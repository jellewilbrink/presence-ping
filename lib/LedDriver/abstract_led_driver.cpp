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

bool AbstractLedDriver::enable_num_leds(uint8_t num)
{
    bool enough_available = (initialized_led_pins.size() >= num);
    int enable_num_leds = enough_available ? num : initialized_led_pins.size();

    // Reset all LEDs
    for (int i = 0; i < initialized_led_pins.size(); i++)
    {
        set_pin_low(initialized_led_pins[i]);
    }

    // Enable the right number of LEDs
    for (int i = 0; i < enable_num_leds; i++)
    {
        set_pin_high(initialized_led_pins[i]);
    }

    return enough_available;
}
