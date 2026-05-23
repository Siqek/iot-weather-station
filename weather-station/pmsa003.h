#ifndef WS_PMSA003_H
#define WS_PMSA003_H

#include <Adafruit_PM25AQI.h>

namespace pmsa003 {

void setup();

bool readSensorData(PM25_AQI_Data& data);

} // namespace pmsa003

#endif // WS_PMSA003_H
