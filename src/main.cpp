

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
        // // Scan
        ble_scanner->scan(kScanTime);

        // Find and switch LEDs
        uint8_t num_devices_with_target_service = 0;
        num_devices_with_target_service += ble_scanner->get_service_uuid_count(0xFCF1); // Android Nearby share
        num_devices_with_target_service += ble_scanner->get_service_uuid_count(0x0000); // Apple Nearby Share

        led_driver->enable_num_leds(num_devices_with_target_service);

        next_scan_millis += kScanInterval;
    }
}

#else // Native

int main(void) {}

#endif // ESP32