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
        return (static_cast<f64>(m_time) / 1000000000.0);
    }

    constexpr u32 asMilliSeconds() const noexcept
    {
        return static_cast<u32>(m_time / 1000000);
    }

    constexpr u64 asMicroSeconds() const noexcept
    {
        return static_cast<u64>(m_time / 1000);
    }

    constexpr u64 asNanoSeconds() const noexcept
    {
        return m_time;
    }

  private:
    u64 m_time = 0;
};

constexpr Time seconds(f64 time)
{
    return { static_cast<u64>(time * 1000000000) };
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
