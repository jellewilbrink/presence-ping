# Presence Ping
An LED indicator of people's presence at home.

This project uses an ESP32 to turn on an LED when a given IP adress is reachable over the network, and turn of the LED when the address is not reachable.

By assigning the smartphones of all inhabitants a known static IP address (this can be done in the router), the reachability of the IP address becomes an indicator of a person's presence.

## Getting started
### Installation
Clone this repository and open it in the [PlatformIO IDE](https://platformio.org/platformio-ide). 

Alternatively, open it in the Arduino IDE, but in this case: remove the `#include "Arduino.h"` line and manually install the libraries listed in [platformio.ini](./platformio.ini).

After you build the circuit and add your configuration, simply upload the code.

### Configuration
Copy [example_secrets.h](./src/example_secrets.h) to a new file called "secrets.h". This file is ignored by git, so you won't accidentally push your WIFI credentials. Change the contents of "secrets.h" to your liking.

Also configure the router to statically assign the desired IP addresses the the desired devices. 

### Circuit
Connect the + pin of an LED to each pin that you defined in the `LED_PINS` array in "secrets.h" and connect a 2 kOhm resistor between the - pin of an LED and the GND pin of the ESP32.


## Troubleshooting
- If the LEDs don't light up after the first upload of the code to the ESP32, uploading a second time might sometimes help.

## Open Source Libraries
Please note that all the libraries used are publicly available under the LGPL v2.1 license:
``` C++
#include <Arduino.h>
#include <WiFi.h>
#include <ESP32Ping.h>
```