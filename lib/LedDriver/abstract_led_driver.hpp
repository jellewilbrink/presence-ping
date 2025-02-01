#ifndef ABSTRACT_LED_DRIVER_H
#define ABSTRACT_LED_DRIVER_H

#include <stdint.h>
#include <array>

// AbstractLedDriver needs these defines. For the target build, Arduino.h brings them,
// but for native we need to define them here.
#ifndef LOW
#define LOW 0x0
#endif

#ifndef HIGH
#define HIGH 0x1
#endif

#ifndef OUTPUT
#define OUTPUT 0x03
#endif

#ifndef MAX_NUMBER_OF_LED_PINS
#ifdef ESP32
#define MAX_NUMBER_OF_LED_PINS 34
#else
#error "MAX_NUMBER_OF_LED_PINS must be defined!"
#endif // ESP32
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