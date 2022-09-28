#pragma once

#include <vector>

#include "Graphics/RenderBuffer.hpp"
#include "Graphics/Shader.hpp"
#include "Graphics/Types.hpp"
#include "Graphics/Vertex.hpp"
#include "Math/Mat4x4.hpp"
#include "Math/Vec2.hpp"

class Texture;
class Renderer
{
    using Vertices = std::vector<Vertex>;
    using Textures = std::vector<const Texture*>;

  public:
    Renderer();

    void begin();
    void draw(RectF dst, RectF src, const Texture* texture);
    void end();

  private:
    static constexpr u32 MaxSprites = 1000;

    struct TextureSlots {
        s32 currSlot;
        s32 prevSlot;
        std::vector<const Texture*> slot;
    };

    s32 getTextureSlot(const Texture* tex);
    void flushBatch();
    void drawBatch();

    void createShader(Vec2F windowSize);

    u32 m_spriteCount;
    RenderBuffer m_renderBuffer;
    TextureSlots m_textureSlots;
    Vertices m_vertices;
    Shader m_shader;
};
