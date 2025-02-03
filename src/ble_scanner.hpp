#ifndef BLE_SCANNER_H
#define BLE_SCANNER_H

#include <stdint.h>
#include "NimBLEDevice.h"

class BleScanner
{
public:
    BleScanner();
    void scan(uint32_t duration);
    bool is_device_found(uint64_t device_address);

private:
    void init();

    NimBLEScan *pScan;
    NimBLEScanResults scan_results;
};

#endif // BLE_SCANNER_H
