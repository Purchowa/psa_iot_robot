#pragma once

#include <cstddef>
#include <cstdint>

namespace Control
{
    enum class Direction : uint8_t
    {
        Left,     // a
        Backward, // s
        Forward,  // w
        Right,    // d
        Stop
    };

    inline constexpr size_t g_directionCount{4};

    class Motors
    {
    public:
        void init();
        void move(Direction direction) const;

    private:
        enum MotorsGPIO : uint8_t
        {
            PWM_B,
            B_IN_2,
            B_IN_1,
            A_IN_1,
            A_IN_2,
            PWM_A
        };

        void motorAForward() const;
        void motorBForward() const;

        void motorABackward() const;
        void motorBBackward() const;

        void motorAStop() const;
        void motorBStop() const;
    };
}