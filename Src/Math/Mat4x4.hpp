#pragma once

#include "Utils/Types.hpp"

template <typename T>
struct Mat4x4 {
    T m[16] = 0;
};

using Mat4x4F = Mat4x4<f32>;

namespace Math {
    inline constexpr Mat4x4F createOrthoView(f32 l, f32 r, f32 t, f32 b, f32 n = 1.f, f32 f = -1.f)
    {
        return Mat4x4F{ 2.f / (r - l), 0.f,           0.f,          -((r + l) / (r - l)),
                        0.f,           2.f / (t - b), 0.f,          -((t + b) / (t - b)),
                        0.f,           0.f,           -2 / (f - n), -((f + n) / (f - n)),
                        0.f,           0.f,           0.f,          1.f };
    };
}  // namespace Math
