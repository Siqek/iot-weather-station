#include "HardwareSerial.h"
#include "pmsa003.h"

#include <Arduino.h>

namespace pmsa003 {

static HardwareSerial pmSerial(1);

static Adafruit_PM25AQI aqi = Adafruit_PM25AQI();
static bool pmsaInitialized = false;

void setup() {
  pmSerial.begin(9600, SERIAL_8N1, 16, 17);

  if (!aqi.begin_UART(&pmSerial)) {
    Serial.println("Could not find PM 2.5 sensor!");
    return;
  }

  pmsaInitialized = true;

  Serial.println("PM25 found!");
}

bool readSensorData(PM25_AQI_Data& data) {
  if (!pmsaInitialized) {
    return false;
  }

  if (!aqi.read(&data)) {
    return false;
  }

  return true;
}

} // namespace pmsa003
