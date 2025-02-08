# Technology consideration

Different technologies can be used to wirelessly detect the presence of a smartphone. These methods have various limitations are taken into consideration when designing this project.

Both the ESP32 and smartphones have built-in WiFi and Bluetooth capabilites, so these will be compared. 

Ideally, no manual action has to be taken on the smartphone that is to be detected, otherwise an app might be installed on the smartphone to do the heavy lifting. Such apps are already available, but might be preceived as an intrusion of the privacy, since these apps can inherently track much more than only presence in a single building/location.

## WiFi
The ESP32 can ping the smartphone to determine if it is present, assuming that the smartphone has a static IP address which the ESP32 knows. However, it turns out that smartphones only repond to incoming pings when they are actively being used (i.e. the screen is active). Otherwise they seem to go to some kind of sleep mode and quickly stop replying the pings. So, this method turns out to be unsuitable.

## Bluetooth Classic
If the MAC address of the smartphone to track is known, the ESP32 could attempt to connect to it every now and then to determine if the smartphone is present.

This might work if the ESP32 has been manually paired with every smartphone to be tracked at least once. However, this requires manual action on the smartphone and is thus seen as disadvantageous in the scope of this project.

Alternatively, the ESP32 attempt pairing to a smartphone that it has not previously been paired with. A rejection could also indicate the presence of the smartphone. However, after some digging on the internet, it seems likely that modern smartphones will not respond at all to pairing requests when they are not in pairing mode, making this concept impossible.

## Bluetooth Low Energy
Smartphones do often advertise their presence via BLE services. These can be detected passively by the ESP32. However, the MAC address of the device is often made random and changed every so often in order to prevent tracking. So it might be impossible to use BLE to specifically track given smartphone based on its address.

Some alternatives to address tracking could be consider. The ESP32 could count the number of devices advertising a specific commonly used service, such as Nearby Share. This would not tell which precise smartphone is present but indicates the total number of people present. Besides, some devices may advertise a unique service, displayname, or manufacturer ID, which could be used to specifically identify the device. However, using this information requires a significantly more complex application on the ESP32 as well as elaborate analysis of the services that each smartphone advertises.