#ifndef WS_MQTT_H
#define WS_MQTT_H

#include <stdint.h>
#include <PubSubClient.h>

namespace mqtt
{

void setup(PubSubClient& client);

void ensureConnection(PubSubClient& client);

void reconnect(PubSubClient& client);

void publish(PubSubClient& client, const char* topic, float data);
void publish(PubSubClient& client, const char* topic, uint16_t data);

} // namespace mqtt

#endif // WS_MQTT_H
