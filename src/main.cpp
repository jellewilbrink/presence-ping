

#ifdef ESP32

#include <Arduino.h>
#include <stdint.h>
#include <array>
#include "led_driver.hpp"
#include "ble_scanner.hpp"
#include "example_secrets.h"

#define MAX_NUMBER_OF_LED_PINS NUM_UUIDs

// const int kNumberOfUuids = NUM_UUIDs;
const std::array<uint64_t, NUM_UUIDs> kUuidList = UUID_LIST;
const std::array<uint8_t, NUM_UUIDs> kLedPinList = LED_PINS;
const uint32_t kScanTime = SCAN_TIME;
const uint32_t kScanInterval = SCAN_INTERVAL;

LedDriver *led_driver;
BleScanner *ble_scanner;

void setup()
{
    led_driver = new LedDriver();
    ble_scanner = new BleScanner();

    // Register LEDs
    for (auto pin : kLedPinList)
        led_driver->init_led(pin);
}

void loop()
{
    static unsigned long next_scan_millis = millis();

    if (millis() >= next_scan_millis)
    {
        // Scan
        ble_scanner->scan(kScanTime);

        // Find and switch LEDs
        assert(kUuidList.size() == kLedPinList.size());
        for (int i = 0; i < kUuidList.size(); i++)
        {
            auto device_address = kUuidList[i];
            auto led_pin = kLedPinList[i];

            if (ble_scanner->is_device_found(device_address))
                led_driver->set_pin_high(led_pin);
            else
                led_driver->set_pin_low(led_pin);
        }

        next_scan_millis += kScanInterval;
    }
}

#else // Native

int main(void) {}

#endif // ESP32