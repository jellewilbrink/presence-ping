#include "ble_scanner.hpp"

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

void BleScanner::init()
{
    NimBLEDevice::init("");
    pScan = NimBLEDevice::getScan();
}
