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
     * Returns the number of devices advertising a given service UUID.
     */
    uint8_t get_service_uuid_count(uint16_t uuid);

    /**
     * Returns the number of devices advertising a given manufacturer ID.
     *
     * \note The bytes of the ID may be flipped compared to what you expect. (e.g. 0x1234 might be 0x3412)
     */
    uint8_t get_manufacturer_id_count(uint16_t id);

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
