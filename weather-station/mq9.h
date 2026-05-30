#ifndef WS_MQ9_H
#define WS_MQ9_H

namespace mq9 {

struct SensorData {
  float methanePpm = 0.f;
  float lpgPpm = 0.f;
  float carbonMonoxidePpm = 0.f;
};

void setup();

bool readSensorData(SensorData& data);

} // namespace mq9

#endif // WS_MQ9_H
