#pragma once

#include "Math/Vec2.hpp"
#include "Utils/Types.hpp"

template <class T>
struct Rect {
    constexpr Rect() = default;
    constexpr Rect(T rx, T ry, T rw, T rh)
        : x{ rx }
        , y{ ry }
        , w{ rw }
        , h{ rh }
    {
    }

    constexpr Rect(const Vec2<T> tl, const Vec2<T> br)
        : x{ tl.x }
        , y{ tl.y }
        , w{ br.x }
        , h{ br.y }
    {
    }

    template <typename U>
    constexpr Rect(const Rect<U>& r)
        : x{ static_cast<T>(r.x) }
        , y{ static_cast<T>(r.y) }
        , w{ static_cast<T>(r.h) }
        , h{ static_cast<T>(r.w) }
    {
    }

    // Need to handle negative case ?
    constexpr bool intersecting(const Rect<T>& r) noexcept
    {
        return (x < r.x + r.w && r.x < x + w && y < r.y + r.h && r.y < y + h);
    }

    T x = 0;
    T y = 0;
    T w = 0;
    T h = 0;
};

using RectU = Rect<u32>;
using RectF = Rect<f32>;
