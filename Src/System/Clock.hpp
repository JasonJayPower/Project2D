#pragma once

#include <chrono>

#include "System/Time.hpp"
#include "Utils/Types.hpp"

class Clock
{
    using ClockType = std::conditional<std::chrono::high_resolution_clock::is_steady,
                                       std::chrono::high_resolution_clock,
                                       std::chrono::steady_clock>::type;
    using TimePoint = std::chrono::time_point<ClockType>;
    static_assert(ClockType::is_steady, "Clock Type is not monotonically increasing.");

  public:
    Clock() = default;

    Time elapsed() const noexcept
    {
        return Time::inNanoseconds((ClockType::now() - m_start).count());
    }

    Time restart() noexcept
    {
        const TimePoint now = ClockType::now();
        Time elapsed        = Time::inNanoseconds((now - m_start).count());
        m_start             = now;
        return elapsed;
    }

  private:
    TimePoint m_start = ClockType::now();
};
