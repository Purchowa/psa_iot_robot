#include "PacketBuilder.hpp"
#include "DataSerializer.hpp"
#include "EnvironmentSensorsReader.hpp"

namespace WS
{
    tcb::span<std::byte> makeEnvironmentDataPacket(const Environment::Data &data)
    {
        static auto envPacketBuffer = WS::makePacketBuffer<Environment::Data>();

        WS::serialize(WS::DataKind::EnvironmentData, data, envPacketBuffer);

        return envPacketBuffer;
    }
    tcb::span<std::byte> makeTofDataPacket(tcb::span<const ToF::DistanceDataType> data)
    {
        static auto tofPacketBuffer = WS::makePacketBuffer<ToF::DistanceDataType[ToF::g_resolution]>();

        WS::serialize(WS::DataKind::ToFData, data, tofPacketBuffer);

        return tofPacketBuffer;
    }
}