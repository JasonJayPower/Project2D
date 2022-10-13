#include "Graphics/Camera.hpp"

Camera::Camera(f32 width, f32 height)
    : m_pos{ 0.f, 0.f }
    , m_proj{ Math::createOrthoView(0.f, width, 0.f, height) }
    , m_projView{ m_proj }
{
}

Vec2F Camera::getViewSize() const
{
    return { (2.f / m_proj.m[0]), -(2.f / m_proj.m[5]) };
}

RectF Camera::getViewBounds() const
{
    return { { m_pos }, getViewSize() };
}

void Camera::follow(Vec2F target)
{
    const Vec2F viewSize = getViewSize();
    m_pos.x              = -viewSize.x * 0.5f + target.x;
    m_pos.y              = -viewSize.y * 0.5f + target.y;
}

void Camera::reset()
{
    m_pos      = { 0.f, 0.f };
    m_projView = m_proj;
}

void Camera::move(const Vec2F pos)
{
    m_pos.x += pos.x;
    m_pos.y += pos.y;
}

void Camera::recalculateMatrix()
{
    m_projView = m_proj * Math::createTranslation(m_pos);
}

const Mat4x4F& Camera::getProjViewMat()
{
    recalculateMatrix();
    return m_projView;
}
