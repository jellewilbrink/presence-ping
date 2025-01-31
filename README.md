# Presence Ping
An LED indicator of people's presence at home.

This project uses an ESP32 to turn on an LED when a given BLE device is detected, and turn of the LED when the device is absent.

## Getting started
### Installation
Clone this repository and open it in the [PlatformIO IDE](https://platformio.org/platformio-ide). 

Alternatively, open it in the Arduino IDE, but in this case: remove the `#include "Arduino.h"` line and manually install the libraries listed in [platformio.ini](./platformio.ini).

After you build the circuit and add your configuration, simply upload the code.

### Configuration
Copy [example_secrets.h](./src/example_secrets.h) to a new file called "secrets.h". This file is ignored by git, so you won't accidentally push secret information. Change the contents of "secrets.h" to your liking.

You will need to add a list of the UUIDs of devices that you want to track the presence of. You can use a separate tool to find the UUIDs, for example [nRFConnect](https://www.nordicsemi.com/Products/Development-tools/nRF-Connect-for-mobile).

### Circuit
Connect the + pin of an LED to each pin that you defined in the `LED_PINS` array in "secrets.h" and connect a 2 kOhm resistor between the - pin of an LED and the GND pin of the ESP32.


## Troubleshooting
- If the LEDs don't light up after the first upload of the code to the ESP32, uploading a second time might sometimes help.

## Contributing
### Unit testing
Unit tests are configured using the built-in options from platformio. The [Unity framework](https://docs.platformio.org/en/latest/advanced/unit-testing/frameworks/unity.html) is chosen.

## Open Source Libraries
Please note that all the libraries used are publicly available under the LGPL v2.1 license:
``` C++
#include <Arduino.h>
#include <WiFi.h>
#include <ESP32Ping.h>
```

## Reading material
- BLE-Scanner: https://github.com/gromeck/BLE-Scanner?tab=readme-ov-file
- NimBLE library: https://github.com/h2zero/NimBLE-Arduino
- List of Bluetooth Company Identifier UUIDs: https://www.bluetooth.com/specifications/assigned-numbers/