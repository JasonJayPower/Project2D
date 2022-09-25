#pragma once

#include <glad/glad.h>

#include "Math/Mat4x4.hpp"
#include "Math/Vec2.hpp"

class Shader : public NonCopyable
{
  public:
    Shader() = default;
    ~Shader();

    void bind() const;
    void unbind() const;

    void create(const c8* vertexData, const c8* fragmentData);

    void setMat4x4F(const c8* name, const Mat4x4F& mat4x4) const;

  private:
    u32 m_handle = 0;
};
