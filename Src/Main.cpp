#include "Graphics/ContextWindow.hpp"
#include "Graphics/Renderer.hpp"
#include "Graphics/Texture.hpp"
#include "Input/Types.hpp"
#include "System/Clock.hpp"

#include "Input/EventHandler.hpp"

struct X {
    void mouseMove(IEventData data) {
        printf("Mouse moved %d, %d \n", data.mousePos.x, data.mousePos.y);
    }
    void btnA(IEventData data) {
        printf("BtnA Pressed %d, %d \n", data.keyboard.key, data.keyboard.mod);
    }
    void btnB(IEventData data) {
        printf("BtnB Pressed %d, %d \n", data.mouse.btn, data.mouse.mod);
    }
};



s32 main(s32 argc, const char* argv[])
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    ContextWindow window("My Title", 640, 480);
    Renderer r(&window, 1000);

    Texture t;
    Texture t1;
    t.loadFromFile("Assets/Texture/minotaur.png");
    t1.loadFromFile("Assets/Texture/minotaur2.png");

    EventHandler eh;
    X x;
    using Callback = Delegate<void(IEventData)>;
    eh.addCallback(IEventAction::MousePos, Callback::bind<&X::mouseMove>(&x));
    eh.addCallback(IEventAction::BtnA,  Callback::bind<&X::btnA>(&x));
    eh.addCallback(IEventAction::BtnB,  Callback::bind<&X::btnB>(&x));

    while (window.isOpen()) {
        IEvent e{};
        // Move to Context Window ?
        while (window.pollEvent(e)) {
            eh.handleEvent(e);
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
    }
    glfwTerminate();

    return 0;
}
