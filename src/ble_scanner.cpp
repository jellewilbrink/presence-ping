#include "ble_scanner.hpp"
#include "ble_scanner_utils.hpp"
#include <Arduino.h>
#include <string>

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

        if (device->haveServiceData())
        {
            uint8_t data_count = device->getServiceDataCount();
            for (uint8_t j = 0; j < data_count; j++)
            {
                if (device->getServiceDataUUID(j) == target_uuid)
                {
                    count++;
                    break; // Found UUID for this device, so go to next device.
                }
            }
        }
    }

    return count;
}

uint8_t BleScanner::get_manufacturer_id_count(uint16_t id)
{
    uint8_t count = 0;

    for (int i = 0; i < scan_results.getCount(); i++)
    {
        const NimBLEAdvertisedDevice *device = scan_results.getDevice(i);

        if (device->haveManufacturerData())
        {
            // Get manufacturer data and convert to hex string (Copied from: NimBLEAdvertisedDevice.cpp)
            auto manufacturer_data = device->getManufacturerData();
            std::string manufacturer_data_string = NimBLEUtils::dataToHexString(reinterpret_cast<const uint8_t *>(manufacturer_data.data()), manufacturer_data.length());

            int manufacturer_id = BleScannerUtils().parse_manufacturer_id(manufacturer_data_string);

            if (manufacturer_id == id)
                count++;
        }
    }

    return count;
}

uint8_t BleScanner::get_apple_find_my_device_count()
{

    uint8_t count = 0;

    for (int i = 0; i < scan_results.getCount(); i++)
    {
        const NimBLEAdvertisedDevice *device = scan_results.getDevice(i);

        if (device->haveManufacturerData())
        {
            // Get manufacturer data and convert to hex string (Copied from: NimBLEAdvertisedDevice.cpp)
            auto manufacturer_data = device->getManufacturerData();
            std::string manufacturer_data_string = NimBLEUtils::dataToHexString(reinterpret_cast<const uint8_t *>(manufacturer_data.data()), manufacturer_data.length());

            if (BleScannerUtils().is_apple_find_my_service(manufacturer_data_string))
                count++;
        }
    }

    return count;
}

uint8_t BleScanner::get_android_nearby_service_uuid_count()
{
    const uint16_t uuid_android_nearby = 0xFCF1;
    return get_service_uuid_count(uuid_android_nearby);
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
