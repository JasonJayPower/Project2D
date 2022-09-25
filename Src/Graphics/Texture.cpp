#include "Graphics/Texture.hpp"

#include <glad/glad.h>

Texture::~Texture()
{
    glDeleteTextures(1, &m_handle);
}

void Texture::bind() const
{
    glBindTexture(GL_TEXTURE_2D, m_handle);
}

void Texture::unbind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

Vec2U Texture::getSize() const
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
