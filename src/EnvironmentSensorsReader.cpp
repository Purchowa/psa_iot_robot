#include "EnvironmentSensorsReader.hpp"

#include "Arduino.h"

namespace 
{
  struct DataRange
  {
    int64_t min;
    int64_t max;
  };

  constexpr DataRange tempRange{.min{-100}, .max{500}};
  constexpr DataRange humidityRange{.min{0}, .max{100}};
}

namespace Environment
{
  Data readData()
  {
    return {
      .temperature{static_cast<float>(random(tempRange.min, tempRange.max)) / 10.f}, 
      .humidity{random(humidityRange.min, humidityRange.max + 1 )}
    };
  }
}