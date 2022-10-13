#pragma once

#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

#include <memory>
#include <queue>

#include "Input/EventHandler.hpp"
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

    void update();

    EventHandler* getEvtHandler();

  private:
    void pollEvents();

    void initialiseMouseEvents();
    void initialiseKeyboardEvents();

    GLFWwindow* createContextWindow(const c8* title, s32 w, s32 h);

    IEventQueue  m_events;
    EventHandler m_evtHandler;
    GLFWwindow*  m_window;
};
