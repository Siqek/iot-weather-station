#include <stdio.h>
#include "mqtt.h"

#include <Arduino.h>

#include "config.h"

namespace mqtt {

void setup(PubSubClient& client) {
  client.setServer(mqtt::SERVER, mqtt::PORT);
}

void ensureConnection(PubSubClient& client) {
  // Ensure we stay connected
  if (!client.connected()) {
    reconnect(client);
  }
  client.loop(); // Keep MQTT alive
}

void reconnect(PubSubClient& client) {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");

    // --- LWT CONFIGURATION ---
    // define Last Will: Topic, QoS, Retain, Message
    // If this ESP32 dies, the Broker will post "offline" to the status topic automatically.

    if (client.connect(mqtt::DEVICE_ID, mqtt::USER, mqtt::PASSWORD, mqtt::topics::STATUS, 1, true, "offline")) {
      Serial.println("connected");

      // Once connected, publish an announcement that we are alive (Retained = true)
      client.publish(mqtt::topics::STATUS, "online", true);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void publish(PubSubClient& client, const char* topic, float data) {
  char msg[16];
  snprintf(msg, sizeof(msg), "%.2f", data);
  client.publish(topic, msg);
}

} // namespace mqtt
