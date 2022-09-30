#pragma once
#include "Utils/Types.hpp"

class Time
{
  public:
    constexpr Time() noexcept
        : m_time{ 0 }
    {
    }

    constexpr Time(u64 time) noexcept
        : m_time{ time }
    {
    }

    constexpr f64 asSeconds() const noexcept
    {
        return static_cast<f64>(m_time / 1000000000.0);
    }

    constexpr s32 asMilliSeconds() const noexcept
    {
        return static_cast<s32>(m_time / 1000000);
    }

    constexpr s64 asMicroSeconds() const noexcept
    {
        return static_cast<s64>(m_time / 1000);
    }

    constexpr s64 asNanoSeconds() const noexcept
    {
        return m_time;
    }

  private:
    u64 m_time = 0;
};

constexpr Time seconds(f64 time)
{
    return Time(static_cast<u64>(time * 1000000000));
}

constexpr Time operator+(Time left, Time right)
{
    return left.asNanoSeconds() + right.asNanoSeconds();
}

constexpr Time& operator+=(Time& left, Time right)
{
    return left = left + right;
}

constexpr Time operator-(Time left, Time right)
{
    return left.asNanoSeconds() - right.asNanoSeconds();
}

constexpr Time& operator-=(Time& left, Time right)
{
    return left = left - right;
}
