#pragma once

#include "Utils/Types.hpp"

template <class T>
struct Vec2 {
    constexpr Vec2() = default;
    constexpr Vec2(T vx, T vy)
        : x{ vx }
        , y{ vy }
    {
    }

    template <typename U>
    constexpr explicit Vec2(const Vec2<U>& v)
        : x{ static_cast<T>(v.x) }
        , y{ static_cast<T>(v.y) }
    {
    }

    T x = 0;
    T y = 0;
};

template <typename T>
constexpr Vec2<T>& operator+=(Vec2<T>& v1, const Vec2<T>& v2) noexcept
{
    v1.x += v2.x;
    v1.y += v2.y;
    return v1;
}

template <typename T>
inline constexpr bool operator==(Vec2<T> v1, Vec2<T> v2) noexcept
{
    return v1.x == v2.x && v1.y == v2.y;
}

template <typename T>
inline constexpr bool operator!=(Vec2<T> v1, Vec2<T> v2) noexcept
{
    return !(v1 == v2);
}

using Vec2S = Vec2<s32>;
using Vec2U = Vec2<u32>;
using Vec2F = Vec2<f32>;
using Vec2D = Vec2<f64>;
