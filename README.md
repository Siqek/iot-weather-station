# IoT Weather Station

An ESP32-based weather station that reads environmental data from multiple sensors and publishes it to an MQTT broker.

## Screenshots

![weather-station](/docs/assets/weather-station.jpg)
![weather-station-top-view](/docs/assets/weather-station-top-view.jpg "top view")

## Wiring

### BME280 (SPI)

| Sensor | ESP32 |
| --- | --- |
| **VCC**@3.3V | **3V3**@3.3V |
| **GND** | **GND** |
| **SCL**@3.3V (SCK) | **D22**@3.3V (GPIO22) |
| **SDA**@3.3V (SDI) | **D21**@3.3V (GPIO21) |


### PMSA003 (UART)

| Sensor | ESP32 |
| --- | --- |
| **VCC**@5V | **VIN**@5V |
| **GND** | **GND** |
| **RX**@3.3V | **TX2**@3.3V (TXD_2 / GPIO17) |
| **TX**@3.3V | **RX2**@3.3V (RXD_2 / GPIO16) |

### MQ9

This sensor will be replaced with different sensor or wiring will be changed to allow switching between 5V and 1.4V.
