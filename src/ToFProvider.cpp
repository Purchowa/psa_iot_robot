#include "ToFProvider.hpp"
#include <Wire.h>

#include <string>
#include <stdexcept>
#include <sstream>

namespace ToF
{
  namespace
  {
    constexpr int rst_pin{9};
    constexpr int tof_SDA_pin{8};
    constexpr int tof_SCL_pin{7};
    constexpr uint32_t tof_I2C_freq{400'000}; // 400kHz

    constexpr uint8_t tof_sampling_freq{15};
  }

  void ImageProvider::init()
  {
    Wire.begin(tof_SDA_pin, tof_SCL_pin, tof_I2C_freq);

    pinMode(rst_pin, OUTPUT);
    digitalWrite(rst_pin, LOW);

    bool isImagerOk{true};

    isImagerOk &= m_imager.begin();
    isImagerOk &= m_imager.setResolution(g_resolution);
    isImagerOk &= m_imager.setRangingFrequency(tof_sampling_freq);
    isImagerOk &= m_imager.startRanging();

    if (!isImagerOk)
    {
      throw std::runtime_error("[ToF] Imager initialization error. Code: " + std::to_string(static_cast<uint8_t>(m_imager.lastError.lastErrorCode)));
    }
  }

  bool ImageProvider::pollData()
  {
    if (m_imager.isDataReady())
    {
      return m_imager.getRangingData(&m_measurementData);
    }

    return false;
  }

  tcb::span<const DistanceDataType> ImageProvider::getDistanceData() const
  {
    return m_measurementData.distance_mm;
  }

  std::string ImageProvider::serializeDistanceData()
  {
    std::ostringstream oss;
    for (const auto distance : m_measurementData.distance_mm)
    {
      oss << distance << " ";
    }

    return oss.str();
  }
}