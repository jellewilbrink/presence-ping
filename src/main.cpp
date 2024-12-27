#include <Arduino.h>
#include <WiFi.h>
#include <ESP32Ping.h>

#include "secrets.h"

// All the constants are defined using '#define' in
// secrets.h according to the types specified here.
const char *ssid = SSID;
const char *password = WIFI_PASSWORD;

const int num_addresses = NUM_ADDRESSES;
const char *ip_adresses[] = IP_ADDRESSES;
const int led_pins[] = LED_PINS;

const int ping_delay = PING_DELAY;

void init_leds()
{
  for (int i = 0; i < num_addresses; i++)
  {
    pinMode(led_pins[i], OUTPUT);
    digitalWrite(led_pins[i], LOW);
  }
}

// Ping given ip adress and switch the LED accordingly
void check_ip_presence(IPAddress ip, int led_pin)
{
  Serial.print("Pinging ip ");
  Serial.println(ip);

  if (Ping.ping(ip))
  {
    Serial.println("Success!!");
    digitalWrite(led_pin, HIGH);
  }
  else
  {
    Serial.println("Error :(");
    digitalWrite(led_pin, LOW);
  }
}

// Ping all ip adresses in the list and switch the LEDS accordingly
void check_ips()
{
  for (int i = 0; i < num_addresses; i++)
  {
    IPAddress ip;
    ip.fromString(ip_adresses[i]);
    check_ip_presence(ip, led_pins[i]);
  }
}

void setup()
{
  Serial.begin(115200);
  delay(10);

  init_leds();

  // Connect to WiFi network
  Serial.println();
  Serial.println("Connecting to WiFi");

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(100);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("WiFi connected with ip ");
  Serial.println(WiFi.localIP());
}

void loop()
{
  check_ips();
  delay(ping_delay);
}