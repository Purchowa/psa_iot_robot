#include "WebSocketReceiver.hpp"

namespace WS
{
  void onEventCallback(WStype_t type, uint8_t *payload, size_t length, const Control::Motors &motorControl)
  {
    switch (type)
    {
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
    {
      if (length < Control::g_directionCount)
      {
        motorControl.move(Control::Direction::Stop);
        break;
      }

      Control::Direction direction = Control::Direction::Stop;
      for (uint8_t i = 0; i < length; ++i)
      {
        if (payload[i])
        {
          direction = static_cast<Control::Direction>(i);
          break;
        }
      }

      motorControl.move(direction);
      break;
    }
    case WStype_ERROR:
    case WStype_FRAGMENT_TEXT_START:
    case WStype_FRAGMENT_BIN_START:
    case WStype_FRAGMENT:
    case WStype_FRAGMENT_FIN:
      break;
    }
  }
}
