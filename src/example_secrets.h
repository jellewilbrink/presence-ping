#define SSID "INSERT WIFI NAME"
#define WIFI_PASSWORD "INSERT WIFI PASSWORD"

// Number of IP addresses to ping
#define NUM_ADDRESSES 2

// List of IP adresses to ping. Length must be NUM_ADDRESSES
#define IP_ADDRESSES {"192.168.2.1", "192.168.2.2"}

// List of GPIO pins for the LEDs. Length must be NUM_ADDRESSES
#define LED_PINS {13, 14}

// Time between consecutive pings in ms
#define PING_DELAY 10000