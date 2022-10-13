#include "Graphics/RenderBuffer.hpp"

#include <vector>

RenderBuffer::RenderBuffer(s32 maxSprites)
    : m_maxSprites{ maxSprites }
    , m_bufferSize{ maxSprites * static_cast<s32>(sizeof(Vertex)) }
    , m_currBuffer{ 0 }
    , m_vao       { 0 }
    , m_vbo       { 0 }
    , m_sbo       { 0 }
{
    createVertexBuffer();
    createSpriteBuffer();
    createVertexArray();
}

RenderBuffer::~RenderBuffer()
{
    glDeleteBuffers(Graphics::MaxBuffers, m_vbo);
    glDeleteBuffers(Graphics::MaxBuffers, m_sbo);
    glDeleteVertexArrays(Graphics::MaxBuffers, m_vao);
}

void RenderBuffer::update(const Vertex* data, s32 count)
{
    const s32 currBufferSize = count * static_cast<s32>(sizeof(Vertex));
    glBindBuffer(GL_ARRAY_BUFFER, m_sbo[m_currBuffer]);

    glBufferData(GL_ARRAY_BUFFER, m_bufferSize, nullptr, GL_DYNAMIC_DRAW);
    void* mapped = glMapBufferRange(GL_ARRAY_BUFFER, 0, m_bufferSize, GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);
    memcpy(mapped, data, currBufferSize);
    glUnmapBuffer(GL_ARRAY_BUFFER);

    glBindVertexArray(m_vao[m_currBuffer]);
    m_currBuffer = (m_currBuffer + 1) % Graphics::MaxBuffers;
}

void RenderBuffer::createVertexArray()
{
    glGenVertexArrays(Graphics::MaxBuffers, m_vao);
    for (size_t i = 0; i < Graphics::MaxBuffers; i++) {
        glBindVertexArray(m_vao[i]);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo[i]);

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(f32), nullptr);

        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, m_sbo[i]);

        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, dst)));
        glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, src)));
        glVertexAttribIPointer(3, 1, GL_UNSIGNED_INT, sizeof(Vertex), (void*)(offsetof(Vertex, tid)));

        glEnableVertexAttribArray(1);  // Destination
        glEnableVertexAttribArray(2);  // Texture Source
        glEnableVertexAttribArray(3);  // Texture Slot/ID

        glVertexAttribDivisor(1, 1);
        glVertexAttribDivisor(2, 1);
        glVertexAttribDivisor(3, 1);
    }
}

void RenderBuffer::createVertexBuffer()
{
    const f32 vertices[] = { 0.f, 0.f, 1.f, 0.f, 0.f, 1.f, 1.f, 1.f };
    glGenBuffers(Graphics::MaxBuffers, m_vbo);
    for (size_t i = 0; i < Graphics::MaxBuffers; i++) {
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo[i]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    }
}

void RenderBuffer::createSpriteBuffer()
{
    glGenBuffers(Graphics::MaxBuffers, m_sbo);
    for (size_t i = 0; i < Graphics::MaxBuffers; i++) {
        glBindBuffer(GL_ARRAY_BUFFER, m_sbo[i]);
        glBufferData(GL_ARRAY_BUFFER, m_bufferSize, nullptr, GL_DYNAMIC_DRAW);
    }
}
