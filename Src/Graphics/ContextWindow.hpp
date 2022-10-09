#pragma once

#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

#include <queue>

#include "Input/Types.hpp"
#include "Math/Vec2.hpp"
#include "Utils/Types.hpp"

class ContextWindow : public NonCopyable
{
  public:
    ContextWindow(const c8* title, s32 w, s32 h);
    ~ContextWindow();

    Vec2S getSize() const;
    bool isOpen() const;
    void close() const;
    void update() const;

    bool pollEvent(IEvent& e);

  private:
    void initialiseCallbacks();

    GLFWwindow* createContextWindow(const c8* title, s32 w, s32 h);

    IEventQueue m_events;
    GLFWwindow* m_window;
};
