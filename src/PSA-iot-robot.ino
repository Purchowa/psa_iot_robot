#include <WiFi.h>

#include "Config.hpp"

#include "EnvironmentSensorsAPI.hpp"
#include "EnvironmentSensorsReader.hpp"
#include "ToFProvider.hpp"
#include "ToFSocketAPI.hpp"

using delay_ms = uint32_t;

Environment::SensorsAPI sensorsApi{Cfg::Api::thingspeakUrl};
ToF::ImageProvider tofImage;
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

  webSocketClient.beginSSL(Cfg::Api::webSocketHostName, Cfg::Api::webSocketPort, Cfg::Api::webSocketUrl);
  webSocketClient.onEvent(onEventCallback);
}

uint32_t callCounter{0};

void loop()
{
  webSocketClient.loop();

  if (httpRequestInterval / tofSensorInterval <= callCounter++)
  {
    const auto httpCode = sensorsApi.postData(Environment::readData());
    Serial.printf("[HTTPS] Post sensor data, code: %d\n", httpCode);
    callCounter = 0;
  }

  if (tofImage.pollData())
  {
    webSocketClient.sendTXT(tofImage.serializeDistanceData().c_str());
  }

  delay(tofSensorInterval);
}
