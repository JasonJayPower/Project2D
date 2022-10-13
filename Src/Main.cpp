#include "Graphics/Camera.hpp"
#include "Graphics/ContextWindow.hpp"
#include "Graphics/Renderer.hpp"
#include "Graphics/Texture.hpp"
#include "Input/EventHandler.hpp"
#include "Input/Types.hpp"

struct Sprite {
    void update()
    {
        dst.x += dir.x * spd;
        dst.y += dir.y * spd;
    }

    s32 spd   = 2;
    Vec2F dir = { 0, 0 };
    RectF dst = { 0, 0, 71, 65 };
    RectF src = { 0, 0, 71, 65 };
    const Texture* tex;

    void up(IEventData data)    { dir = {  0, -1 }; }
    void down(IEventData data)  { dir = {  0,  1 }; }
    void left(IEventData data)  { dir = { -1,  0 }; }
    void right(IEventData data) { dir = {  1,  0 }; }
};

s32 main(s32 argc, const char* argv[])
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    ContextWindow window("My Title", 640, 480);

    Renderer r(&window, 10);

    Camera c(640, 480);

    Texture t;
    Texture t1;
    t.loadFromFile("Assets/Texture/minotaur.png");
    t1.loadFromFile("Assets/Texture/minotaur2.png");

    Sprite s;
    s.tex = &t;

    using Callback = Delegate<void(IEventData)>;

    auto eh = window.getEvtHandler();
    eh->addCallback(IEventAction::Up,    Callback::bind<&Sprite::up>(&s));
    eh->addCallback(IEventAction::Down,  Callback::bind<&Sprite::down>(&s));
    eh->addCallback(IEventAction::Left,  Callback::bind<&Sprite::left>(&s));
    eh->addCallback(IEventAction::Right, Callback::bind<&Sprite::right>(&s));

    while (window.isOpen()) {
        s.update();
        c.follow({ s.dst.x + s.dst.w / 2, s.dst.y + s.dst.h / 2 });

        r.clear();
        r.begin(&c);
        r.draw(s.dst, s.src, &t);
        for (size_t i = 0; i < 20; i++) {
            r.draw({ f32(rand() % 600), f32(rand() % 480), 71, 65 }, { 0, 0, 71, 65 }, &t1);
        }
        
        r.end();

        window.update();
    }
    glfwTerminate();

    return 0;
}
