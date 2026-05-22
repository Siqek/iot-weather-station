#ifndef WS_BME280_H
#define WS_BME280_H

namespace bme280 {

void setup();

bool readTemperature(float& outTemperature);

bool readHumidity(float& outHumidity);

bool readPressure(float& outPressure);

} // namespace bme280

#endif // WS_BME280_H
