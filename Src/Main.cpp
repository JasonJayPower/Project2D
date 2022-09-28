#include <iostream>

#include "Graphics/ContextWindow.hpp"
#include "Graphics/Renderer.hpp"
#include "Graphics/Texture.hpp"
#include "Input/Types.hpp"

s32 main(s32 argc, const s8* argv[])
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    ContextWindow window("My Title", 640, 480);
    Renderer r;

    Texture t;
    Texture t1;
    t.loadFromFile("Assets/Texture/minotaur.png");
    t1.loadFromFile("Assets/Texture/minotaur2.png");

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
        r.begin();
        for (size_t i = 0; i < 10; i++) {
            r.draw({ f32(rand() % 550), f32(rand() % 430), 71, 65 }, { 0, 0, 71, 65 }, &t);
            r.draw({ f32(rand() % 550), f32(rand() % 430), 71, 65 }, { 0, 0, 71, 65 }, &t1);
        }
        r.end();

        window.update();
    }
    glfwTerminate();

    return 0;
}
