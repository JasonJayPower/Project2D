#pragma once

#include "Math/Vec2.hpp"
#include "Utils/Types.hpp"

class Texture : public NonCopyable
{
  public:
    Texture() = default;
    ~Texture();

    void bind() const;
    void unbind() const;

    Vec2U getSize() const;

    bool create1x1();

  private:
    u32 m_handle = 0;
    u32 m_width  = 0;
    u32 m_height = 0;
};
