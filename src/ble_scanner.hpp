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

    /**
     * Scan for BLE devices and print the results to serial console for debugging purposes.
     *
     * \note This function makes no assumptions about Serial.begin(baud_rate) having been
     * called before, so it will call it just to be sure.
     */
    void scan_and_print(uint32_t duration, unsigned long baud_rate);

private:
    void init();

    NimBLEScan *pScan;
    NimBLEScanResults scan_results;
};

#endif // BLE_SCANNER_H
