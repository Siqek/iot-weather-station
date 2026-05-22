#include "wifi_manager.h"

#include <Arduino.h>
#include <WiFi.h>

#include "config.h"

namespace wifi {

void setup() {
  delay(10);

  Serial.println();
  Serial.print("Connecting to WiFi: ");
  Serial.println(wifi::SSID);

  WiFi.mode(WIFI_STA);
  WiFi.begin(wifi::SSID, wifi::PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void ensureConnection() {
  if (WiFi.status() != WL_CONNECTED) {
    WiFi.reconnect();
  }
}

} // namespace wifi
