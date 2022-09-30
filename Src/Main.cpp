#include "Graphics/ContextWindow.hpp"
#include "Graphics/Renderer.hpp"
#include "Graphics/Texture.hpp"
#include "Input/Keyboard.hpp"
#include "Input/Types.hpp"
#include "System/Clock.hpp"

s32 main(s32 argc, const s8* argv[])
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    ContextWindow window("My Title", 640, 480);
    Renderer r(&window, 100000);

    Texture t;
    Texture t1;
    t.loadFromFile("Assets/Texture/minotaur.png");
    t1.loadFromFile("Assets/Texture/minotaur2.png");

    Keyboard kb;

    while (window.isOpen()) {
        IEvent e{};
        while (window.pollEvent(e)) {
            switch (e.type) {
                case IEventType::KeyPressed:
                case IEventType::KeyReleased: {
                    kb.setKey(e.keyboard.key);
                } break;
            }
        }

        if (kb.checkKeyAndState(GLFW_KEY_ESCAPE, IState::Press)) {
            window.close();
        }
        if (kb.checkKeyAndState(GLFW_KEY_A, IState::Press)) {
            printf("Key A has been pressed\n");
        }
        if (kb.checkKeyAndState(GLFW_KEY_S, IState::Release)) {
            printf("Key S has been released\n");
        }
        if (kb.checkKeyAndState(GLFW_KEY_D, IState::Hold)) {
            printf("Key D is held\n");
        }

        glClearColor(0.39f, 0.58f, 0.93f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        r.begin();
        for (size_t i = 0; i < 25; i++) {
            r.draw({ f32(rand() % 550), f32(rand() % 430), 71, 65 }, { 0, 0, 71, 65 }, &t);
            r.draw({ f32(rand() % 550), f32(rand() % 430), 71, 65 }, { 0, 0, 71, 65 }, &t1);
        }
        r.end();

        window.update();
        kb.update();
    }
    glfwTerminate();

    return 0;
}
