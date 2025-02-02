#ifndef ABSTRACT_LED_DRIVER_H
#define ABSTRACT_LED_DRIVER_H

#include <stdint.h>
#include <array>

#ifdef ESP32
#include "esp32-hal-gpio.h"
#ifndef MAX_NUMBER_OF_LED_PINS
#define MAX_NUMBER_OF_LED_PINS 34
#endif // MAX_NUMBER_OF_LED_PINS
#endif // ESP32

// Check required defines.
#ifndef LOW
#error "LOW must be defined!"
#endif // LOW
#ifndef HIGH
#error "HIGH must be defined!"
#endif // HIGH
#ifndef OUTPUT
#error "OUTPUT must be defined!"
#endif // OUTPUT
#ifndef MAX_NUMBER_OF_LED_PINS
#error "MAX_NUMBER_OF_LED_PINS must be defined!"
#endif // MAX_NUMBER_OF_LED_PINS

class AbstractLedDriver
{
public:
    AbstractLedDriver();
    void init_led(uint8_t pin);
    bool set_pin_high(uint8_t pin);
    bool set_pin_low(uint8_t pin);
    bool is_led_pin_initialized(uint8_t pin);

protected:
    virtual void set_pin_mode(uint8_t pin, uint8_t mode) = 0;
    virtual void set_pin_state(uint8_t pin, uint8_t val) = 0;

private:
    uint8_t number_of_initialized_pins;
    std::array<uint8_t, MAX_NUMBER_OF_LED_PINS> initialized_led_pins;
};

#endif