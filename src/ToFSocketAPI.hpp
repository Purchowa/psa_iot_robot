#pragma once

#include "Arduino.h"

#include <SocketIOclient.h>

extern SocketIOclient g_socketIOClient;

void onEventCallback(socketIOmessageType_t type, uint8_t * payload, size_t length);
String prepareEvent(String eventName);

namespace ToF
{

  class WebSocketApi
  {
    public:
      WebSocketApi(const char* hostName, const char* url);
      void connectAndListen();
      void emitToFCameraData();

    private:
      static void onStateCallback(socketIOmessageType_t type, uint8_t * payload, size_t length);

      SocketIOclient m_webSocket{};

      String m_hostName;
      String m_customUrl;
  };
}