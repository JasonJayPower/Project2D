#pragma once

#include "Utils/Types.hpp"

template <class T>
struct Vec2 {
    constexpr Vec2(T vx, T vy)
        : x{ vx }
        , y{ vy }
    {
    }

    template <typename U>
    constexpr Vec2(const Vec2<U>& v)
        : x{ static_cast<T>(v.x) }
        , y{ static_cast<T>(v.y) }
    {
    }

    T x = 0;
    T y = 0;
};

using Vec2S = Vec2<s32>;
using Vec2U = Vec2<u32>;
using Vec2F = Vec2<f32>;
using Vec2D = Vec2<f64>;
