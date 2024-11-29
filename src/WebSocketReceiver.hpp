#pragma once

#include "Motors.hpp"
#include <WebSocketsClient.h>

namespace WS
{
  void onEventCallback(WStype_t type, uint8_t *payload, size_t length, const Control::Motors &motorControl);
}
