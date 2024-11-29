#pragma once

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <type_traits>

#include "span.hpp"

namespace WS
{
    enum class DataKind : uint8_t
    {
        ToFData,
        EnvironmentData
    };

    template <typename T>
    auto makePacketBuffer()
    {
        std::array<std::byte, sizeof(DataKind) + sizeof(T)> buffer{};

        return buffer;
    }

    template <typename T>
    void serialize(DataKind dataKind, const T *data, size_t dataSize, tcb::span<std::byte> dst)
    {
        if (dst.size_bytes() < dataSize + sizeof(DataKind))
            assert("Destinantion buffer is too small to perform serialization");

        const auto dataKindNum = static_cast<std::underlying_type_t<DataKind>>(dataKind);
        std::memcpy(dst.data(), reinterpret_cast<const void *>(&dataKindNum), sizeof(DataKind));
        std::memcpy(dst.data() + sizeof(DataKind), reinterpret_cast<const void *>(data), dataSize);
    }

    template <typename T>
    void serialize(DataKind dataKind, const T &data, tcb::span<std::byte> dst)
    {
        serialize(dataKind, &data, sizeof(data), dst);
    }

    template <typename T>
    void serialize(DataKind dataKind, const tcb::span<T> &data, tcb::span<std::byte> dst)
    {
        serialize(dataKind, data.data(), data.size_bytes(), dst);
    }
}