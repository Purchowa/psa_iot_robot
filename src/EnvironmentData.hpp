#pragma once

#include <cstdint>

namespace Environment
{
  #pragma pack(push, 1)
  struct  Data
  {
    float temperature;
    uint16_t humidity;
  };
  #pragma pack(pop)
}