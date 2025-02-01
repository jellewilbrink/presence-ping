#ifndef ABSTRACT_LED_DRIVER_H
#define ABSTRACT_LED_DRIVER_H

#include <stdint.h>

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

class AbstractLedDriver
{
public:
    void init_led(uint8_t pin);

protected:
    virtual void set_pin_mode(uint8_t pin, uint8_t mode) = 0;
    virtual void set_pin_state(uint8_t pin, uint8_t val) = 0;
};

#endif