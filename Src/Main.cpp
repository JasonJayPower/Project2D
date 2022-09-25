#include <GLAD/glad.h>

#include "Graphics/ContextWindow.hpp"
#include "Graphics/Shader.hpp"
#include "Graphics/Texture.hpp"
#include "Input/Types.hpp"
#include "Math/Mat4x4.hpp"

#include <iostream>

inline constexpr c8* vsData = R"(
    #version 330 core
    layout (location = 0) in vec2 dst;
    layout (location = 1) in vec2 src;
    out vec2 oSrc;
    uniform mat4 vproj;
    void main() {
        oSrc = src;
        gl_Position = vproj * vec4(dst, 0.f, 1.f); 
    }  
)";

inline constexpr c8* fsData = R"(
    #version 330 core
    out vec4 FragColor;
    in  vec2 src;
    uniform sampler2D image;
    void main() { 
        FragColor = texelFetch(image, ivec2(src), 0);
    };
)";

inline constexpr u32 indices[]  = { 0, 1, 2, 2, 3, 0 };
inline constexpr f32 vertices[] = {
    // Pos          // Src
      0.0f,   0.0f, 0.f, 0.f, 
    100.0f,   0.0f, 1.f, 0.f, 
    100.0f, 100.0f, 1.f, 1.f, 
      0.0f, 100.0f, 0.f, 1.f
};

s32 main(s32 argc, const s8* argv[])
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    ContextWindow window("My Title", 640, 480);

    Shader s;
    s.create(vsData, fsData);
    s.setMat4x4F("vproj", Math::createOrthoView(0.f, 640.f, 0.f, 480.f));

    Texture t;
    t.create1x1();
    t.bind();

    u32 vao = 0;
    u32 vbo = 0;
    u32 ibo = 0;

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(u32) * 6, &indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(f32), 0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(f32), (void*)(2 * sizeof(float)));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    while (window.isOpen()) {
        IEvent e{};
        while (window.pollEvent(e)) {
            switch (e.type) {
                case IEventType::KeyPressed: {
                    std::cout << "Key " << e.keyboard.key << " pressed" << std::endl;
                } break;
                case IEventType::KeyReleased: {
                    std::cout << "Key " << e.keyboard.key << " released" << std::endl;
                } break;
            }
        }

        glClearColor(0.39f, 0.58f, 0.93f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        window.update();
    }
    glfwTerminate();

    return 0;
}
