#pragma once

#include <vector>

#include "Graphics/RenderBuffer.hpp"
#include "Graphics/Shader.hpp"
#include "Graphics/Types.hpp"
#include "Graphics/Vertex.hpp"
#include "Math/Mat4x4.hpp"
#include "Math/Vec2.hpp"

class ContextWindow;
class Texture;
class Renderer : NonCopyable
{
    using Vertices = std::vector<Vertex>;
    using Textures = std::vector<const Texture*>;

  public:
    Renderer(const ContextWindow* cWindow, u32 m_numSpritesPerBatch = 64);

    void resetView();

    void begin();
    void draw(RectF dst, RectF src, const Texture* texture);
    void end();

  private:
    struct TextureSlots {
        s32 currSlot;
        s32 prevSlot;
        std::vector<const Texture*> slot;
    };

    s32 getTextureSlot(const Texture* tex);
    void flushBatch();
    void drawBatch();

    void createShader();

    u32          m_spriteCount;
    u32          m_batchSize;
    Vec2S        m_windowSize;
    RenderBuffer m_renderBuffer;
    TextureSlots m_textureSlots;
    Vertices     m_vertices;
    Shader       m_shader;
};
