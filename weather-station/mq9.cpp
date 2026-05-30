#include "esp32-hal.h"
#include "esp32-hal-gpio.h"
#include "mq9.h"

#include <Arduino.h>
#include <MQUnifiedsensor.h>
#include <stdint.h>

namespace mq9 {

namespace gas_curves {

struct GasCurve { float a = 0.f, b = 0.f; };

inline constexpr const GasCurve LPG{ 1000.5, -2.186 };

inline constexpr const GasCurve METHANE{ 4269.6, -2.648 };

inline constexpr const GasCurve CARBON_MONOXIDE{ 599.65, -2.244 };

} // namespace gas_curves

/************************Hardware Related Constexpres************************************/
static constexpr const char*   Board              = "ESP-32";
static constexpr const int     Pin                = 36; // GPIO36 (VP on board)
/************************Software Related Constexpres************************************/
static constexpr const char*   Type               = "MQ-9";
static constexpr const float   Voltage_Resolution = 3.3f;
static constexpr const int     ADC_Bit_Resolution = 12;
static constexpr const float   RatioMQ9CleanAir   = 9.6f;

static MQUnifiedsensor mq9(Board, Voltage_Resolution, ADC_Bit_Resolution, Pin, Type);
static bool mq9Initialized = false;

bool calibrate() {
  float calcR0 = 0.f;
  for (int i = 0; i < 10; ++i) {
    mq9.update();
    calcR0 += mq9.calibrate(RatioMQ9CleanAir);
  }

  mq9.setR0(calcR0/10);

  if (isinf(calcR0) || calcR0 == 0) {
    return false;
  }
  return true;
}

void setup() {
  mq9.setRegressionMethod(2); // use linear method

  mq9.setA(mq9::gas_curves::LPG.a);
  mq9.setB(mq9::gas_curves::LPG.b);

  mq9.init();

  delay(60000);
  if (!calibrate()) {
    return;
  }

  mq9Initialized = true;

  /* important note:
   *
   * usage of ESP32 board causes a problem that we can't control heat voltage without additional hardware (e.g. MOSFET)
   *
   * due to ESP32 operating on 3.3 volts, we can only connect constant 5 volts supply to the heater
   *
   * therefore constant heating with 5 volts gives us inaccurate value of carbon monoxide concentration
   *
   * moreover this also prevents us from using the preheating cycle (60 seconds at 5 volts then 90 seconds at 1.4 volts) before R0 calibration
   *
  */
}

bool readSensorData(SensorData& data) {
  if (!mq9Initialized) {
    return false;
  }
  mq9.update();

  mq9.setA(mq9::gas_curves::LPG.a);
  mq9.setB(mq9::gas_curves::LPG.b);
  data.lpgPpm = mq9.readSensor();

  mq9.setA(mq9::gas_curves::METHANE.a);
  mq9.setB(mq9::gas_curves::METHANE.b);
  data.methanePpm = mq9.readSensor();

  mq9.setA(mq9::gas_curves::CARBON_MONOXIDE.a);
  mq9.setB(mq9::gas_curves::CARBON_MONOXIDE.b);
  data.carbonMonoxidePpm = mq9.readSensor();

  return true;
}

} // namespace mq9
