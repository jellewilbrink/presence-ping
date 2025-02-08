#include "ble_scanner_utils.hpp"

int BleScannerUtils::parse_manufacturer_id(std::string manufacturer_data)
{
    std::string manufacturer_id = manufacturer_data.substr(0, 4);
    int manufacturer_id_int = std::stoi(manufacturer_id, nullptr, 16);
    return manufacturer_id_int;
}