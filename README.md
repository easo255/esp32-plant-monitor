# 🌱 esp32-plant-monitor
A simple plant monitor that uses a [capacitive moisture sensor](https://wiki.seeedstudio.com/Grove-Capacitive_Moisture_Sensor-Corrosion-Resistant/) connected to a [TTGO T-Display ESP32](https://www.banggood.com/LILYGO-TTGO-T-Display-ESP32-CP2104-WiFi-bluetooth-Module-1_14-Inch-LCD-Development-Board-p-1522925.html?akmClientCountry=NO&cur_warehouse=UK).

A button on the ESP is configured to conduct a reading of moisture in the plant, and simultaneously send a POST request to a Firebase Function which logs the reading in a firestore database.

## Usage of Code

Configure the code with your SSID, password and eventually a URL for logging the values in a database, or remove the code that sends requests if you only want to display the reading on the display.
