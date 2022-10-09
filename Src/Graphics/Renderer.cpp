#include "Graphics/Renderer.hpp"

#include "Graphics/Consts.hpp"
#include "Graphics/ContextWindow.hpp"
#include "Graphics/Texture.hpp"
#include "Utils/GLHelpers.hpp"

Renderer::Renderer(const ContextWindow* cWindow, s32 numSpritesPerBatch)
    : m_spriteCount { 0 }
    , m_batchSize   { numSpritesPerBatch }
    , m_windowSize  { cWindow->getSize() }
    , m_renderBuffer{ numSpritesPerBatch }
    , m_vertices    { Vertices(numSpritesPerBatch) }
    , m_textureSlots{ 0, 0, Textures(GLHelpers::getMaxTextureUnits()) }
{
    createShader();
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Renderer::resetView()
{
    m_shader.setUniformMatrix4fv(
        Graphics::ProjViewUniform,
        Math::createOrthoView(0.f, static_cast<f32>(m_windowSize.x), 0.f, static_cast<f32>(m_windowSize.y)));
}

void Renderer::begin()
{
}

void Renderer::draw(RectF dst, RectF src, const Texture* texture)
{
    const u32 texSlot = getTextureSlot(texture);
    if (m_spriteCount >= m_batchSize) {
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
            m_shader.setCustomUniform1iv(Graphics::TextureUniform, texSlot);
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

void Renderer::createShader()
{
    m_shader.create(Graphics::VSData, Graphics::FSData);
    m_shader.setUniformMatrix4fv(Graphics::ProjViewUniform,
        Math::createOrthoView(0.f, static_cast<f32>(m_windowSize.x), 0.f, static_cast<f32>(m_windowSize.y)));
}
