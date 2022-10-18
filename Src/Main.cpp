#include "Graphics/Camera.hpp"
#include "Graphics/ContextWindow.hpp"
#include "Graphics/Renderer.hpp"
#include "Graphics/Texture.hpp"
#include "Input/EventHandler.hpp"
#include "Input/Types.hpp"
#include "System/Clock.hpp"

struct Sprite {
    void update()
    {
        dst.x += dir.x * spd;
        dst.y += dir.y * spd;
    }

    s32 spd            = 4;
    Vec2F dir          = { 0, 0 };
    Vec2F pre          = { 0, 0 };
    Vec2F cur          = { 0, 0 };
    RectF dst          = { 100, 100, 71, 65 };
    RectF src          = { 0, 0, 71, 65 };
    const Texture* tex = nullptr;

    void up(IEventData)
    {
        dir = { 0, -1 };
    }
    void down(IEventData)
    {
        dir = { 0, 1 };
    }
    void left(IEventData)
    {
        dir = { -1, 0 };
    }
    void right(IEventData)
    {
        dir = { 1, 0 };
    }
};

Vec2F interpolate(Vec2F prev, Vec2F curr, f32 alpha)
{
    return { curr.x * alpha + (prev.x * (1.f - alpha)), curr.y * alpha + (prev.y * (1.f - alpha)) };
}
    #include <iostream>
s32 main(s32, const char*[])
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
    t1.loadFromFile("Assets/Texture/bg.png");

    Sprite s;
    s.tex = &t;

    using Callback = Delegate<void(IEventData)>;

    auto eh = window.getEvtHandler();
    eh->addCallback(IEventAction::Up, Callback::bind<&Sprite::up>(&s));
    eh->addCallback(IEventAction::Down, Callback::bind<&Sprite::down>(&s));
    eh->addCallback(IEventAction::Left, Callback::bind<&Sprite::left>(&s));
    eh->addCallback(IEventAction::Right, Callback::bind<&Sprite::right>(&s));

    constexpr Time FrameTime = Time::inSeconds(1.f / 60.f);

    Clock gameClock;
    Time timeSinceLastUpdate = FrameTime;

    while (window.isOpen()) {
        timeSinceLastUpdate += gameClock.elapsed();
        if (timeSinceLastUpdate >= FrameTime) {
            timeSinceLastUpdate -= FrameTime;
            s.update();
            c.follow({ s.dst.x, s.dst.y });
        }

        r.clear();
        r.begin(&c);
        r.draw({ 0, 0, 1000, 1000 }, { 0, 0, 10, 10 }, &t1);
        r.draw(s.dst, s.src, &t);
        r.end();

        // Render / Input
        window.update();
    }
    glfwTerminate();

    return 0;
}
