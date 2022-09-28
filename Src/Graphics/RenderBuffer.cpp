#include "Graphics/RenderBuffer.hpp"

#include <vector>

RenderBuffer::RenderBuffer(const u32 maxSprites)
    : m_vao{ 0 }
    , m_vbo{ 0 }
    , m_ibo{ 0 }
    , m_sbo{ 0 }
{
    createVertexBuffer();
    createSpriteBuffer(maxSprites);
    createVertexArray();
    createIndexBuffer();
}

RenderBuffer::~RenderBuffer()
{
    glDeleteBuffers(1, &m_vbo);
    glDeleteBuffers(1, &m_ibo);
    glDeleteBuffers(1, &m_sbo);
    glDeleteVertexArrays(1, &m_vao);
}

void RenderBuffer::update(const Vertex* data, s32 count)
{
    glBindBuffer(GL_ARRAY_BUFFER, m_sbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, count * sizeof(Vertex), data);
}

void RenderBuffer::createVertexArray()
{
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(f32), nullptr);

    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, m_sbo);

    glVertexAttribPointer( 1, 4,  GL_FLOAT,        GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, dst)));
    glVertexAttribPointer( 2, 4,  GL_FLOAT,        GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, src)));
    glVertexAttribIPointer(3, 1,  GL_UNSIGNED_INT,           sizeof(Vertex), (void*)(offsetof(Vertex, tid)));

    glEnableVertexAttribArray(1);  // Destination
    glEnableVertexAttribArray(2);  // Texture Source
    glEnableVertexAttribArray(3);  // Texture Slot/ID

    glVertexAttribDivisor(1, 1);
    glVertexAttribDivisor(2, 1);
    glVertexAttribDivisor(3, 1);
}

void RenderBuffer::createVertexBuffer()
{
    const f32 vertices[] = { 0.f, 0.f, 1.f, 0.f, 1.f, 1.f, 0.f, 1.f };
    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

void RenderBuffer::createIndexBuffer()
{
    const u32 indices[] = { 0, 1, 2, 2, 3, 0 };
    glGenBuffers(1, &m_ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

void RenderBuffer::createSpriteBuffer(const u32 maxSprites)
{
    glGenBuffers(1, &m_sbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_sbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * maxSprites, nullptr, GL_DYNAMIC_DRAW);
}
