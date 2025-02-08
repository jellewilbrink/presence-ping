#ifndef BLE_SCANNER_UTILS_H
#define BLE_SCANNER_UTILS_H

#include <stdint.h>
#include <string>

class BleScannerUtils
{
public:
    /**
     * Returns the manufacturer id (first 2 bytes of manufacturer data).
     */
    int parse_manufacturer_id(std::string manufacturer_data);
};

#endif // BLE_SCANNER_UTILS_H
