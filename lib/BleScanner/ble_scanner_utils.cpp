#include "ble_scanner_utils.hpp"

int BleScannerUtils::parse_manufacturer_id(std::string manufacturer_data)
{
    std::string manufacturer_id = manufacturer_data.substr(0, 4);
    int manufacturer_id_int = std::stoi(manufacturer_id, nullptr, 16);
    return manufacturer_id_int;
}

bool BleScannerUtils::is_apple_find_my_service(std::string manufacturer_data)
{
    if (manufacturer_data.length() < 6)
        return false;

    const uint16_t id_apple = 0x4c00; // Apple
    const uint8_t service_byte_find_my = 0x12;
    std::string service_byte = manufacturer_data.substr(4, 2);
    int service_byte_int = std::stoi(service_byte, nullptr, 16);

    return (parse_manufacturer_id(manufacturer_data) == id_apple) && (service_byte_int == service_byte_find_my);
}
