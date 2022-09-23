#include <GLAD/glad.h>

#include <iostream>

#include "Graphics/ContextWindow.hpp"
#include "Input/Types.hpp"

s32 main(s32 argc, const s8* argv[])
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    ContextWindow window("My Title", 640, 480);

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

        window.update();
    }
    glfwTerminate();

    return 0;
}
