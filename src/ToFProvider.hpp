#pragma once

#include <SparkFun_VL53L5CX_Library.h>

#include "span.hpp"

namespace ToF
{
  class ImageProvider
  {
    public:
      void init();
      bool pollData();

      tcb::span<const int16_t> getDistanceData();

    private:
      SparkFun_VL53L5CX m_imager{};
      VL53L5CX_ResultsData m_measurementData{};
  };
}