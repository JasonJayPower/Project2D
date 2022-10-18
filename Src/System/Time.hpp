#pragma once

#include "Utils/Types.hpp"

class Time
{
  public:
    constexpr Time() = default;

    constexpr s64 asNanoSeconds() const noexcept
    {
        return m_ns.count();
    }

    constexpr f32 asSeconds() const noexcept
    {
        return std::chrono::duration<f32>(m_ns).count();
    }

    template <typename T, typename = std::enable_if_t<std::is_integral_v<T>>>
    static constexpr Time inNanoseconds(T ns)
    {
        return Time(std::chrono::nanoseconds(ns));
    }

    template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
    static constexpr Time inSeconds(T s)
    {
        return Time(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::duration<T>(s)));
    }

  private:
    template <typename Rep, typename Period>
    constexpr Time(const std::chrono::duration<Rep, Period>& duration)
        : m_ns{ duration }
    {
    }

    std::chrono::nanoseconds m_ns{ 0 };
};

constexpr Time operator+(Time t1, Time t2)
{
    return Time::inNanoseconds(t1.asNanoSeconds() + t2.asNanoSeconds());
}

constexpr Time& operator+=(Time& t1, Time t2)
{
    return t1 = t1 + t2;
}

constexpr Time operator-(Time t1, Time t2)
{
    return Time::inNanoseconds(t1.asNanoSeconds() - t2.asNanoSeconds());
}

constexpr Time& operator-=(Time& t1, Time t2)
{
    return t1 = t1 - t2;
}

constexpr bool operator<(Time t1, Time t2)
{
    return t1.asNanoSeconds() < t2.asNanoSeconds();
}

constexpr bool operator>(Time t1, Time t2)
{
    return t1.asNanoSeconds() > t2.asNanoSeconds();
}

constexpr bool operator<=(Time t1, Time t2)
{
    return t1.asNanoSeconds() <= t2.asNanoSeconds();
}

constexpr bool operator>=(Time t1, Time t2)
{
    return t1.asNanoSeconds() >= t2.asNanoSeconds();
}
