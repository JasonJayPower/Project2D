#pragma once

#include "Math/Vec2.hpp"
#include "Utils/Types.hpp"

struct Mat4x4F {
    f32 m[16] = { 1.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f, 1.f };
};

inline constexpr Mat4x4F operator*(const Mat4x4F& lhs, const Mat4x4F& rhs)
{
    Mat4x4F res;
    res.m[0] = lhs.m[0] * rhs.m[0] + lhs.m[1] * rhs.m[4];
    res.m[1] = lhs.m[0] * rhs.m[1] + lhs.m[1] * rhs.m[5];
    res.m[3] = lhs.m[0] * rhs.m[3] + lhs.m[1] * rhs.m[7] + lhs.m[3];
    res.m[4] = lhs.m[4] * rhs.m[0] + lhs.m[5] * rhs.m[4];
    res.m[5] = lhs.m[4] * rhs.m[1] + lhs.m[5] * rhs.m[5];
    res.m[7] = lhs.m[4] * rhs.m[3] + lhs.m[5] * rhs.m[7] + lhs.m[7];
    return res;
}

namespace Math {
    inline constexpr Mat4x4F createOrthoView(f32 l, f32 r, f32 t, f32 b, f32 n = 1.f, f32 f = -1.f)
    {
        return Mat4x4F{ 2.f / (r - l), 0.f,           0.f,          -((r + l) / (r - l)),
                        0.f,           2.f / (t - b), 0.f,          -((t + b) / (t - b)),
                        0.f,           0.f,           -2 / (f - n), -((f + n) / (f - n)),
                        0.f,           0.f,           0.f,          1.f };
    }

    inline constexpr Mat4x4F createTranslation(Vec2F t)
    {
        return Mat4x4F{ 1.f, 0.f, 0.f, -t.x, 0.f, 1.f, 0.f, -t.y, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f, 1.f };
    }
}  // namespace Math
