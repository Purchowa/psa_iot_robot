#include "ToFSocketAPI.hpp"

#include <ArduinoJson.h>

void onEventCallback(WStype_t type, uint8_t *payload, size_t length)
{
   switch(type) {
   case WStype_DISCONNECTED:
     Serial.printf("[WSc] Disconnected!\n");
     break;
   case WStype_CONNECTED:
     Serial.printf("[WSc] Connected to url: %s\n", payload);
     break;
   case WStype_TEXT:
     Serial.printf("[WSc] get text: %s\n", payload);
     break;
   case WStype_BIN:
     Serial.printf("[WSc] get binary length: %u\n", length);
     break;
   case WStype_ERROR:
   case WStype_FRAGMENT_TEXT_START:
   case WStype_FRAGMENT_BIN_START:
   case WStype_FRAGMENT:
   case WStype_FRAGMENT_FIN:
     break;
    }
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

  // void WebSocketApi::connectAndListen()
  // {
  //   m_webSocket.onEvent(WebSocketApi::onStateCallback);

  //   m_webSocket.beginSSL(m_hostName, sslPort, m_customUrl + "/?EIO=3");
  // }

  // void WebSocketApi::onStateCallback(socketIOmessageType_t type, uint8_t * payload, size_t length)
  // {
  //   Serial.printf("%s\n", payload);
  // }
}