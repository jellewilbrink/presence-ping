#ifdef ESP32

#include <Arduino.h>
#include "led_driver.hpp"

LedDriver *led_driver;

void setup()
{
    led_driver = new LedDriver();
}

void loop() {}

#else // Native

int main(void) {}

#endif // ESP32