#include "Motors.hpp"

#include <Wire.h>
#include <array>

namespace Control
{
    void Motors::init()
    {
        static constexpr std::array motorGPIOs = {PWM_B, B_IN_2, B_IN_1, A_IN_1, A_IN_2, PWM_A};
        for (const auto gpio : motorGPIOs)
        {
            pinMode(gpio, OUTPUT);
        }
    }

    void Motors::move(Direction direction) const
    {
        switch (direction)
        {
        case Direction::Backward:
        {
            motorAForward();
            motorBForward();
            break;
        }
        case Direction::Forward:
        {
            motorABackward();
            motorBBackward();
            break;
        }
        case Direction::Left:
        {
            motorABackward();
            motorBForward();
            break;
        }
        case Direction::Right:
        {
            motorAForward();
            motorBBackward();
            break;
        }
        default:
        {
            motorAStop();
            motorBStop();
            digitalWrite(PWM_A, LOW);
            digitalWrite(PWM_B, LOW);

            return;
        }
        }

        digitalWrite(PWM_A, HIGH);
        digitalWrite(PWM_B, HIGH);
    }

    void Motors::motorAForward() const
    {
        digitalWrite(A_IN_1, HIGH);
        digitalWrite(A_IN_2, LOW);
    }

    void Motors::motorBForward() const
    {
        digitalWrite(B_IN_1, LOW);
        digitalWrite(B_IN_2, HIGH);
    }

    void Motors::motorABackward() const
    {
        digitalWrite(A_IN_1, LOW);
        digitalWrite(A_IN_2, HIGH);
    }

    void Motors::motorBBackward() const
    {
        digitalWrite(B_IN_1, HIGH);
        digitalWrite(B_IN_2, LOW);
    }

    void Motors::motorAStop() const
    {
        digitalWrite(A_IN_1, LOW);
        digitalWrite(A_IN_2, LOW);
    }

    void Motors::motorBStop() const
    {
        digitalWrite(B_IN_1, LOW);
        digitalWrite(B_IN_2, LOW);
    }
}