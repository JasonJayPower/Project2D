#pragma once
#include <GLAD/glad.h>

#include "Graphics/Consts.hpp"
#include "Graphics/Vertex.hpp"
#include "Utils/Types.hpp"

class RenderBuffer
{
  public:
    RenderBuffer(s32 maxSprites);
    ~RenderBuffer();

    void update(const Vertex* data, s32 count);

  private:
    void createVertexBuffer();
    void createSpriteBuffer();
    void createVertexArray();

    s32 m_maxSprites;
    s32 m_bufferSize;
    s32 m_currBuffer;
    u32 m_vao[Graphics::MaxBuffers];
    u32 m_vbo[Graphics::MaxBuffers];
    u32 m_sbo[Graphics::MaxBuffers];
};
