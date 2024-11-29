#pragma once

#include "ToFProvider.hpp"
#include "EnvironmentData.hpp"
#include "span.hpp"

namespace WS
{
    tcb::span<std::byte> makeEnvironmentDataPacket(const Environment::Data &data);
    tcb::span<std::byte> makeTofDataPacket(tcb::span<const ToF::DistanceDataType> data);
}