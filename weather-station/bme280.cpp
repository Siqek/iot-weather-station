#include "Arduino.h"
#include "bme280.h"

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BME280.h>

namespace bme280 {

static Adafruit_BME280 bme; // use I2C interface
static bool bmeInitialized = false;

static Adafruit_Sensor *bmeTemp = bme.getTemperatureSensor();
static Adafruit_Sensor *bmePressure = bme.getPressureSensor();
static Adafruit_Sensor *bmeHumidity = bme.getHumiditySensor();

void setup() {
  if (!bme.begin(0x76)) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    return;
  }

  bmeInitialized = true;

  Serial.println("BME280 sensors details:");
  bmeTemp->printSensorDetails();
  bmePressure->printSensorDetails();
  bmeHumidity->printSensorDetails();
}

bool readTemperature(float& outTemperature) {
  if (!bmeInitialized) {
    return false;
  }

  sensors_event_t temperatureEvent;
  bmeTemp->getEvent(&temperatureEvent);
  outTemperature = temperatureEvent.temperature;
  return true;
}

bool readHumidity(float& outHumidity) {
  if (!bmeInitialized) {
    return false;
  }

  sensors_event_t humidityEvent;
  bmeHumidity->getEvent(&humidityEvent);
  outHumidity = humidityEvent.relative_humidity;
  return true;
}

bool readPressure(float& outPressure) {
  if (!bmeInitialized) {
    return false;
  }
  sensors_event_t pressureEvent;
  bmePressure->getEvent(&pressureEvent);
  outPressure = pressureEvent.pressure;
  return true;
}

} // namespace bme280
