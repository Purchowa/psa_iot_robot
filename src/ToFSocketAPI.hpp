#pragma once

#include "Arduino.h"

#include <WebSocketsClient.h>

void onEventCallback(WStype_t type, uint8_t *payload, size_t length);

namespace ToF
{
  class WebSocketApi
  {
    public:
      WebSocketApi(const char* hostName, const char* url);
      // void connectAndListen();
      void emitToFCameraData();

    private:
      // static void onStateCallback(socketIOmessageType_t type, uint8_t * payload, size_t length);

      WebSocketsClient m_webSocket{};

      String m_hostName;
      String m_customUrl;
  };
}