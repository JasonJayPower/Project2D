#include "Graphics/Texture.hpp"

#include <GLAD/glad.h>
#include <STB/stb_image.h>

Texture::~Texture()
{
    glDeleteTextures(1, &m_handle);
}

void Texture::bind(u32 slot) const
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_handle);
}

void Texture::unbind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

Vec2S Texture::getSize() const
{
    return { m_width, m_height };
}

bool Texture::create1x1()
{
    m_width  = 1;
    m_height = 1;

    const u32 pixel = 0xFFFFFFFF;

    glGenTextures(1, &m_handle);
    glBindTexture(GL_TEXTURE_2D, m_handle);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &pixel);
    return true;
}

bool Texture::loadFromFile(const char* filepath)
{
    u8* pixelData{ stbi_load(filepath, &m_width, &m_height, &m_comp, 0) };
    if (pixelData) {
        glGenTextures(1, &m_handle);
        glBindTexture(GL_TEXTURE_2D, m_handle);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        switch (m_comp) {
            case STBI_rgb_alpha: {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixelData);
            } break;
            default: {
                printf("Bit-Depth of .png not supported, supporting only 32-bit.\n");
            }
        }
        stbi_image_free(pixelData);
    }
    return true;
}
