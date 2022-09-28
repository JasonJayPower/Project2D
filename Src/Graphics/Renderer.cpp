#include "Graphics/Renderer.hpp"

#include "Graphics/ContextWindow.hpp"
#include "Graphics/Texture.hpp"
#include "Utils/GLHelpers.hpp"

Renderer::Renderer()
    : m_spriteCount { 0 }
    , m_renderBuffer{ 32 }
    , m_vertices    { Vertices(32) }
    , m_textureSlots{ 0, 0, Textures(GLHelpers::getMaxTextureUnits()) }
{
    createShader(Vec2F{ 640.f, 480.f });
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Renderer::begin()
{
}

void Renderer::draw(RectF dst, RectF src, const Texture* texture)
{
    const u32 texSlot = getTextureSlot(texture);
    if (m_spriteCount >= 128) {
        flushBatch();
    }

    m_vertices[m_spriteCount] = { dst, src, texSlot };
    m_spriteCount++;
}

void Renderer::end()
{
    flushBatch();
}

s32 Renderer::getTextureSlot(const Texture* tex)
{
    s32 texSlot = m_textureSlots.prevSlot;
    if (tex != m_textureSlots.slot[texSlot]) {
        const auto it = std::find(std::begin(m_textureSlots.slot), std::end(m_textureSlots.slot), tex);
        texSlot       = it != m_textureSlots.slot.end() ? it - m_textureSlots.slot.cbegin() : -1;
        if (texSlot == -1) {
            if (m_textureSlots.currSlot >= m_textureSlots.slot.size()) {
                m_textureSlots.currSlot = m_textureSlots.prevSlot = 0;
                flushBatch();
            }
            texSlot = m_textureSlots.prevSlot = m_textureSlots.currSlot++;
            m_textureSlots.slot[texSlot]      = tex;
            tex->bind(texSlot);
            m_shader.setCustomUniform1iv("image", texSlot);
        }
    }
    return texSlot;
}

void Renderer::flushBatch()
{
    drawBatch();
    m_spriteCount = 0;
}

void Renderer::drawBatch()
{
    m_renderBuffer.update(m_vertices.data(), m_spriteCount);
    glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr, m_spriteCount);
}

void Renderer::createShader(Vec2F windowSize)
{
    static constexpr c8* vsData = R"(
        #version 330 core
        layout (location = 0) in vec2 vOffset;
        layout (location = 1) in vec4 vDst;
        layout (location = 2) in vec4 vSrc;
        layout (location = 3) in uint vTid;
        uniform mat4 vproj;
             out vec2 fOffset;
             out vec4 fSrc;
        flat out uint fTid;
        void main() {
            fOffset = vOffset;
            fSrc = vSrc;
            fTid = vTid;
            gl_Position = vproj * vec4((vOffset * vDst.zw) + vDst.xy, 0.f, 1.f); 
        }  
    )";

    static constexpr c8* fsData = R"(
        #version 330 core
        in vec2 fOffset;
             in vec4 fSrc;
        flat in uint fTid;
        out vec4 Color;
        uniform sampler2D image[5];
        void main() { 
            Color = texelFetch(image[fTid], ivec2((fOffset * fSrc.zw) + fSrc.xy), 0);
        };
    )";

    m_shader.create(vsData, fsData);
    m_shader.setUniformMatrix4fv("vproj", Math::createOrthoView(0.f, 640.f, 0.f, 480.f));
}
