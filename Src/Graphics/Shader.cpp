#include "Graphics/Shader.hpp"

Shader::~Shader()
{
    glDeleteProgram(m_handle);
}

void Shader::bind() const
{
    glUseProgram(m_handle);
}

void Shader::unbind() const
{
    glUseProgram(0);
}

void Shader::create(const c8* vsData, const c8* fsData)
{
    u32 vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vsData, nullptr);
    glCompileShader(vs);

    u32 fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fsData, nullptr);
    glCompileShader(fs);

    m_handle = glCreateProgram();
    glAttachShader(m_handle, vs);
    glAttachShader(m_handle, fs);
    glLinkProgram(m_handle);

    glDeleteShader(vs);
    glDeleteShader(fs);

    glUseProgram(m_handle);
}

void Shader::setCustomUniform1iv(const c8* name, s32 data) const
{
    // (REVISIT) Sets the value of a specific index for a uniform array.
    glUniform1iv(glGetUniformLocation(m_handle, name) + data, 1, &data);
}

void Shader::setUniformMatrix4fv(const c8* name, const Mat4x4F& mat4x4) const
{
    glUniformMatrix4fv(glGetUniformLocation(m_handle, name), 1, true, &mat4x4.m[0]);
}
