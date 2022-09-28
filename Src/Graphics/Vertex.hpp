#pragma once

#include "Math/Rect.hpp"

struct Vertex {
    RectF dst = { 0.f, 0.f, 0.f, 0.f };
    RectF src = { 0.f, 0.f, 0.f, 0.f };
    u32   tid = 0;
};
