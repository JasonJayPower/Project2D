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

    Vec2S getSize() const;

    bool create1x1();
    bool loadFromFile(const char* filepath);

  private:
    u32 m_handle = 0;
    s32 m_width  = 0;
    s32 m_height = 0;
    s32 m_comp   = 0;
};
