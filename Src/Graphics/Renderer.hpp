#pragma once

#include <vector>

#include "Graphics/RenderBuffer.hpp"
#include "Graphics/Shader.hpp"
#include "Graphics/Vertex.hpp"
#include "Math/Mat4x4.hpp"
#include "Math/Vec2.hpp"

class Camera;
class ContextWindow;
class Texture;
class Renderer : NonCopyable
{
    using Vertices = std::vector<Vertex>;
    using Textures = std::vector<const Texture*>;

  public:
    explicit Renderer(const ContextWindow* cWindow, s32 m_numSpritesPerBatch = 64);

    void resetView();

    void clear() const;
    void begin(Camera* camera = nullptr);
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

    s32          m_spriteCount;
    s32          m_batchSize;
    Vec2S        m_winSize;
    RenderBuffer m_renderBuffer;
    TextureSlots m_textureSlots;
    Vertices     m_vertices;
    Shader       m_shader;
};
