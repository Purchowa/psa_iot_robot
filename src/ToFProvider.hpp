#pragma once

#include <SparkFun_VL53L5CX_Library.h>

#include "span.hpp"

namespace ToF
{
  using DistanceDataType = int16_t;
  constexpr uint8_t g_resolution{64};

  class ImageProvider
  {
    public:
      void init();
      bool pollData();

      tcb::span<const DistanceDataType> getDistanceData() const;
      std::string serializeDistanceData();

    private:
      SparkFun_VL53L5CX m_imager{};
      VL53L5CX_ResultsData m_measurementData{};
  };
}