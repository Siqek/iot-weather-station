#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

#include "wifi_manager.h"
#include "mqtt.h"
#include "bme280.h"
#include "pmsa003.h"

#include "config.h"

WiFiClient espClient;
PubSubClient client(espClient); // MQTT client

void setup() {
  Serial.begin(115200);

  delay(3000);

  wifi::setup();
  mqtt::setup(client);

  bme280::setup();
  pmsa003::setup();
}

static float temperature = 0.f;
static float humidity = 0.f;
static float pressure = 0.f;
static PM25_AQI_Data aqiData{};

void loop() {
  wifi::ensureConnection();
  mqtt::ensureConnection(client);

  if (bme280::readTemperature(temperature)) {
    mqtt::publish(client, mqtt::topics::TEMPERATURE_LAST, temperature);
  }

  if (bme280::readHumidity(humidity)) {
    mqtt::publish(client, mqtt::topics::HUMIDITY_LAST, humidity);
  }

  if (bme280::readPressure(pressure)) {
    mqtt::publish(client, mqtt::topics::PRESSURE_LAST, pressure);
  }

  if (pmsa003::readSensorData(aqiData)) {
    mqtt::publish(client, mqtt::topics::PM1_0_LAST, aqiData.pm10_env);
    mqtt::publish(client, mqtt::topics::PM2_5_LAST, aqiData.pm25_env);
    mqtt::publish(client, mqtt::topics::PM10_LAST, aqiData.pm100_env);
  }

  delay(500);
}
