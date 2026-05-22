#ifndef WS_CONFIG_H
#define WS_CONFIG_H

namespace wifi {

inline constexpr const char* SSID = "";
inline constexpr const char* PASSWORD = "";

} // namespace wifi

namespace mqtt {

inline constexpr const char* SERVER   = "";
inline constexpr const int   PORT     = 1883;
inline constexpr const char* USER     = ""; // Leave blank for public brokers
inline constexpr const char* PASSWORD = "";

// Unique Device ID (Must be unique on the broker)
inline constexpr const char* DEVICE_ID = "ESP32_Weather_Station";

namespace topics {

inline constexpr const char* STATUS = "esp32/weather-station/status"; // LWT (Online/Offline)
inline constexpr const char* TEMPERATURE_LAST  = "esp32/weather-station/temperature/last";
inline constexpr const char* TEMPERATURE_AVG10 = "esp32/weather-station/temperature/avg10";
inline constexpr const char* HUMIDITY_LAST = "esp32/weather-station/humidity/last";
inline constexpr const char* PRESSURE_LAST = "esp32/weather-station/pressure/last";

} // namespace topics

} // namespace mqtt

#endif // WS_CONFIG_H
