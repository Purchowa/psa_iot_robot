#include <WiFi.h>

#include "EnvironmentSensorsAPI.hpp"
#include "EnvironmentSensorsReader.hpp"
#include "ToFProvider.hpp"
#include "ToFSocketAPI.hpp"

using delay_ms = uint32_t;

const char *ssid{"TP-LINK-BLACK"};
const char *password{"smart56."};

const char *imageWebSocketURI{};

Environment::SensorsAPI sensorsApi{"https://api.thingspeak.com/update?api_key=5EVBAPDR1QWR5DCJ"};

// ToF::WebSocketApi tofApi{"at-waterscreen.ddnsking.com", "/api/socket.io"}; // TODO: add hostname
ToF::ImageProvider tofImage{};

constexpr delay_ms delaySecond{1000};

constexpr delay_ms tofSensorInterval{100};
constexpr delay_ms httpRequestInterval{10 * delaySecond};

static_assert(tofSensorInterval <= httpRequestInterval, "ToF getting interval better be smaller!");

void setup()
{
  Serial.begin(115200);
  delay(delaySecond);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print('.');
    delay(500);
  }
  delay(delaySecond);

  // try
  // {
  //   tofImage.init();
  // }
  // catch (const std::runtime_error &exception)
  // {
  //   Serial.println(exception.what());
  //   while (true)
  //     ;
  // }

  g_webSocketClient.beginSSL("echo.websocket.org", 443);
  g_webSocketClient.onEvent(onEventCallback);
}

uint32_t callCounter{0};

void loop()
{
  g_webSocketClient.loop();
  g_webSocketClient.sendTXT("Hello");
  /*
    if (tofImage.pollData())
    {


      for (const auto distance : tofImage.getDistanceData())
      {
        Serial.print(distance);
        Serial.print(' ');
      }
      Serial.print('\n');

    }
     */

  // Serial.printf("[SocketIO] isConnected: %d\n", g_socketIOClient.isConnected());

  // String event = prepareEvent("getState");
  // Serial.printf("[SocketIO] Sending event: %s\n", event);

  if (httpRequestInterval / tofSensorInterval <= callCounter++)
  {
    // socketIOClient.disconnect();
    // const auto httpCode = sensorsApi.postData(Environment::readData());
    // Serial.printf("[HTTPS] Post sensor data, code: %d\n", httpCode);
    callCounter = 0;
  }

  delay(tofSensorInterval);
}
