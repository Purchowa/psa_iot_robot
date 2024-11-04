#include "ToFSocketAPI.hpp"

#include <ArduinoJson.h>

SocketIOclient g_socketIOClient{};

void onEventCallback(socketIOmessageType_t type, uint8_t * payload, size_t length)
{
   switch(type) {
        case sIOtype_DISCONNECT:
            Serial.printf("[IOc] Disconnected!\n");
            break;
        case sIOtype_CONNECT:
            Serial.printf("[IOc] Connected to url: %s\n", payload);
            // join default namespace (no auto join in Socket.IO V3)
            // g_socketIOClient.send(sIOtype_CONNECT, "/");
      
            break;
        case sIOtype_EVENT:
            Serial.printf("[IOc] get event: %s\n", payload);
            break;
        case sIOtype_ACK:
            Serial.printf("[IOc] get ack: %u\n", length);
            break;
        case sIOtype_ERROR:
            Serial.printf("[IOc] get error: %u\n", length);
            break;
        case sIOtype_BINARY_EVENT:
            Serial.printf("[IOc] get binary: %u\n", length);
            break;
        case sIOtype_BINARY_ACK:
            Serial.printf("[IOc] get binary ack: %u\n", length);
            break;
          default:
            Serial.printf("[IOc] unknown: %s\n", payload);
    }
}

String prepareEvent(String eventName)
{
  DynamicJsonDocument doc(1024);
  JsonArray array = doc.to<JsonArray>();

  // add evnet name
  // Hint: socket.on('event_name', ....
  array.add(eventName);

  // JSON to String (serializion)
  String output;
  serializeJson(doc, output);

  return output;
}

namespace ToF
{
  namespace
  {
    constexpr uint16_t sslPort{443};
  }

  WebSocketApi::WebSocketApi(const char* hostName, const char* url) : m_hostName(hostName), m_customUrl(url)
  {
  }

  void WebSocketApi::connectAndListen()
  {
    m_webSocket.onEvent(WebSocketApi::onStateCallback);

    m_webSocket.beginSSL(m_hostName, sslPort, m_customUrl + "/?EIO=3");
  }

  void WebSocketApi::onStateCallback(socketIOmessageType_t type, uint8_t * payload, size_t length)
  {
    Serial.printf("%s\n", payload);
  }
  
}