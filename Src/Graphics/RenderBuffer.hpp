#pragma once
#include <GLAD/glad.h>

#include "Graphics/Vertex.hpp"
#include "Utils/Types.hpp"

class RenderBuffer
{
  public:
    RenderBuffer(s32 maxSprites);
    ~RenderBuffer();

    void update(const Vertex* data, s32 count) const;

  private:
    void createVertexBuffer();
    void createIndexBuffer();
    void createSpriteBuffer(u32 maxSprites);
    void createVertexArray();

    u32 m_vao = 0;  // Vertex Array  Obj
    u32 m_vbo = 0;  // Vertex Buffer Obj
    u32 m_ibo = 0;  // Index  Buffer Obj
    u32 m_sbo = 0;  // Sprite Buffer Obj
};
