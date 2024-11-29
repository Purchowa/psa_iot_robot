#pragma once
#include <stdint.h>

namespace Cfg
{
    namespace WiFi
    {
        inline constexpr auto ssid{""};
        inline constexpr auto password{""};
    }

    namespace Api
    {
        inline constexpr auto webSocketHostName{""};
        inline constexpr auto webSocketUrl{""};
        inline constexpr uint16_t webSocketPort{443};
    }
}