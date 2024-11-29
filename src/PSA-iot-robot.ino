#include <WiFi.h>

#include "Config.hpp"

#include "EnvironmentSensorsReader.hpp"
#include "ToFProvider.hpp"
#include "WebSocketReceiver.hpp"
#include "DataSerializer.hpp"
#include "PacketBuilder.hpp"

using delay_ms = uint32_t;

ToF::ImageProvider tofImage;
Control::Motors motorControl;

WebSocketsClient webSocketClient;

constexpr delay_ms delaySecond{1000};

constexpr delay_ms tofSensorSendInterval{32};
constexpr delay_ms environmentDataSendInterval{delaySecond};

static_assert(tofSensorSendInterval <= environmentDataSendInterval, "ToF getting interval better be smaller!");

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

uint32_t callCounter{0};
void loop()
{
  webSocketClient.loop();

  if (webSocketClient.isConnected())
  {
    if (tofImage.pollData())
    {
      const auto tofPacketData = WS::makeTofDataPacket(tofImage.getDistanceData());
      webSocketClient.sendBIN(reinterpret_cast<const uint8_t *>(tofPacketData.data()), tofPacketData.size_bytes());
    }

    if (environmentDataSendInterval / tofSensorSendInterval <= callCounter++)
    {
      const auto envPacketData = WS::makeEnvironmentDataPacket(Environment::readData());
      webSocketClient.sendBIN(reinterpret_cast<const uint8_t *>(envPacketData.data()), envPacketData.size_bytes());

      callCounter = 0;
    }
  }

  delay(tofSensorSendInterval);
}
