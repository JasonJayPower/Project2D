#pragma once

#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

#include <queue>

#include "Graphics/Types.hpp"
#include "Input/Types.hpp"
#include "Utils/Types.hpp"

class ContextWindow
{
    using EventQueue = std::queue<IEvent>;

  public:
    ContextWindow(const c8* title, s32 w, s32 h);

    bool isOpen() const;
    void close() const;
    void update() const;

    bool pollEvent(IEvent& e);

  private:
    void initialiseCallbacks();

    Window createContextWindow(const c8* title, s32 w, s32 h);

    EventQueue m_events;
    Window m_window;
};
