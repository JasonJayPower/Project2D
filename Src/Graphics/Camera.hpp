#pragma once

#include "Math/Mat4x4.hpp"
#include "Math/Rect.hpp"
#include "Math/Vec2.hpp"
#include "Utils/Types.hpp"

class Camera
{
  public:
    Camera(f32 width, f32 height);

    Vec2F getViewSize() const;

    RectF getViewBounds() const;

    void follow(Vec2F target);

    void reset();

    void move(const Vec2F pos);

    const Mat4x4F& getProjViewMat();

  private:
    void recalculateMatrix();

    Vec2F   m_pos;
    Mat4x4F m_proj;
    Mat4x4F m_projView;
};