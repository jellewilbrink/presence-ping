#ifndef LED_DRIVER_H
#define LED_DRIVER_H
#include <stdint.h>
#include "abstract_led_driver.hpp"
#include "Arduino.h"

class LedDriver : public AbstractLedDriver
{
public:
protected:
    void set_pin_mode(uint8_t pin, uint8_t mode) { pinMode(pin, mode); };
    void set_pin_state(uint8_t pin, uint8_t val) { digitalWrite(pin, val); };
};

#endif // LED_DRIVER_H
