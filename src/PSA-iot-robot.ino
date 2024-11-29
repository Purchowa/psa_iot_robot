#include <WiFi.h>

#include "Config.hpp"

#include "EnvironmentSensorsAPI.hpp"
#include "EnvironmentSensorsReader.hpp"
#include "ToFProvider.hpp"
#include "WebSocketReceiver.hpp"

using delay_ms = uint32_t;

Environment::SensorsAPI sensorsApi{Cfg::Api::thingspeakUrl};
ToF::ImageProvider tofImage;
Control::Motors motorControl;

WebSocketsClient webSocketClient;

constexpr delay_ms delaySecond{1000};

constexpr delay_ms tofSensorInterval{32};
constexpr delay_ms httpRequestInterval{delaySecond};

static_assert(tofSensorInterval <= httpRequestInterval, "ToF getting interval better be smaller!");

void setup()
{
  Serial.begin(115200);
  delay(delaySecond);

  WiFi.begin(Cfg::WiFi::ssid, Cfg::WiFi::password);

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print('.');
    delay(500);
  }
  delay(delaySecond);

  try
  {
    tofImage.init();
  }
  catch (const std::runtime_error &exception)
  {
    Serial.println(exception.what());
    while (true)
      ;
  }

  motorControl.init();

  webSocketClient.beginSSL(Cfg::Api::webSocketHostName, Cfg::Api::webSocketPort, Cfg::Api::webSocketUrl);
  webSocketClient.onEvent([&motorCtrl = motorControl](WStype_t type, uint8_t *payload, size_t length)
                          { WS::onEventCallback(type, payload, length, motorCtrl); });
}

void loop()
{
  webSocketClient.loop();

  if (tofImage.pollData() && webSocketClient.isConnected())
  {
    const auto distanceData = tofImage.getDistanceData();
    webSocketClient.sendBIN(reinterpret_cast<const uint8_t *>(distanceData.data()), distanceData.size_bytes());
  }

  delay(tofSensorInterval);
}
