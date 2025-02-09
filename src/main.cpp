

#ifdef ESP32

#include <Arduino.h>
#include <stdint.h>
#include <array>
#include "led_driver.hpp"
#include "ble_scanner.hpp"
#include "example_secrets.h"
#include "MovingMeanFilter.hpp"
#include "MovingMinFilter.hpp"

#define MAX_NUMBER_OF_LED_PINS NUM_UUIDs

// const int kNumberOfUuids = NUM_UUIDs;
const std::array<uint64_t, NUM_UUIDs> kUuidList = UUID_LIST;
const std::array<uint8_t, NUM_UUIDs> kLedPinList = LED_PINS;
const uint32_t kScanTime = SCAN_TIME;
const uint32_t kScanInterval = SCAN_INTERVAL;
const size_t kMovingMeanWindowSize = 3;
const size_t kMovingMinWindowSize = 600; // Assuming 1 scan per minute, 600 samples == 10 hours

LedDriver *led_driver;
BleScanner *ble_scanner;
MovingMeanFilter *mov_mean;
MovingMinFilter *mov_min;

void setup()
{
    led_driver = new LedDriver();
    ble_scanner = new BleScanner();
    mov_mean = new MovingMeanFilter(kMovingMeanWindowSize);
    mov_min = new MovingMinFilter(kMovingMinWindowSize);

    Serial.begin(115200);

    // // Register LEDs
    // for (auto pin : kLedPinList)
    //     led_driver->init_led(pin);
}

void loop()
{
    static unsigned long next_scan_millis = millis();
    static uint8_t mean = 0;
    static uint8_t baseline = 0;
    static uint8_t num_smartphones_detected = 0;

    if (millis() >= next_scan_millis)
    {
        // // Scan
        ble_scanner->scan_and_print(kScanTime, 115200);

        // Find and switch LEDs
        uint8_t num_devices_with_target_service = 0;
        num_devices_with_target_service += ble_scanner->get_android_nearby_service_uuid_count();
        num_devices_with_target_service += ble_scanner->get_apple_find_my_device_count();

        mov_mean->add_sample(num_devices_with_target_service);
        mean = mov_mean->calculate();

        mov_min->add_sample(mean);
        baseline = mov_min->calculate();

        num_smartphones_detected = mean - baseline;

        // led_driver->enable_num_leds(num_devices_with_target_service);
        Serial.print("Number of smartphones detected: ");
        Serial.println(num_smartphones_detected);

        next_scan_millis += kScanInterval;
    }
}

#else // Native

int main(void) {}

#endif // ESP32