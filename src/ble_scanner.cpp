#include "ble_scanner.hpp"
#include <Arduino.h>

BleScanner::BleScanner()
{
    init();
}

void BleScanner::scan(uint32_t duration)
{
    scan_results = pScan->getResults(duration);
}

bool BleScanner::is_device_found(uint64_t device_address)
{
    // BLE address type. For other options see nimble/ble.h
    static const uint8_t ble_address_type = 0x02; // BLE_ADDR_PUBLIC_ID.
    NimBLEAddress nimble_address(device_address, ble_address_type);

    return scan_results.getDevice(nimble_address) != nullptr ? true : false;
}

uint8_t BleScanner::get_service_uuid_count(uint16_t uuid)
{
    uint8_t count = 0;
    NimBLEUUID target_uuid(uuid);

    for (int i = 0; i < scan_results.getCount(); i++)
    {
        const NimBLEAdvertisedDevice *device = scan_results.getDevice(i);
        if (device->isAdvertisingService(target_uuid))
            count++;
    }

    return count;
}

void BleScanner::scan_and_print(uint32_t duration, unsigned long baud_rate)
{
    Serial.begin(baud_rate);

    Serial.print("Scanning for ");
    Serial.print(duration);
    Serial.println(" ms.");
    scan(duration); // Blocking scan

    int num_found = scan_results.getCount();
    Serial.print("Found ");
    Serial.print(num_found);
    Serial.println(" devices:");

    for (int i = 0; i < num_found; i++)
    {
        const NimBLEAdvertisedDevice *device = scan_results.getDevice(i);
        std::string dev_string = device->toString();
        Serial.println(dev_string.c_str());

        Serial.print("RSSI: ");
        Serial.print(device->getRSSI());
        Serial.println("");
        Serial.println("");
    }
    Serial.println("");
    Serial.println("");
}

void BleScanner::init()
{
    NimBLEDevice::init("");
    pScan = NimBLEDevice::getScan();
}
