#include "Graphics/ContextWindow.hpp"

ContextWindow::ContextWindow(const c8* title, s32 w, s32 h)
    : m_events    {}
    , m_evtHandler{}
    , m_window    { createContextWindow(title, w, h) }
{
    initialiseKeyboardEvents();
    //initialiseMouseEvents();
}

ContextWindow::~ContextWindow()
{
    glfwDestroyWindow(m_window);
}

Vec2S ContextWindow::getSize() const
{
    Vec2S size;
    glfwGetWindowSize(m_window, &size.x, &size.y);
    return size;
}

bool ContextWindow::isOpen() const
{
    return !glfwWindowShouldClose(m_window);
}

void ContextWindow::close() const
{
    glfwSetWindowShouldClose(m_window, true);
}

void ContextWindow::pollEvents()
{
    glfwPollEvents();
    while (!m_events.empty()) {
        m_evtHandler.handleEvent(m_events.front());
        m_events.pop();
    }
}

void ContextWindow::update()
{
    glfwSwapBuffers(m_window);
    pollEvents();
}

EventHandler* ContextWindow::getEvtHandler()
{
    return &m_evtHandler;
}

GLFWwindow* ContextWindow::createContextWindow(const c8* title, s32 w, s32 h)
{
    GLFWwindow* window = glfwCreateWindow(w, h, title, nullptr, nullptr);
    if (window) {
        glfwMakeContextCurrent(window);
        gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
        glfwSwapInterval(1);
    }
    return window;
}

void ContextWindow::initialiseMouseEvents()
{
    glfwSetWindowUserPointer(m_window, &m_events);

    glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, f64 xPos, f64 yPos) {
        auto events = static_cast<IEventQueue*>(glfwGetWindowUserPointer(window));
        events->emplace(IEvent{ IEventType::MouseMoved, { static_cast<s32>(xPos), static_cast<s32>(yPos) } });
    });

    glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, s32 button, s32 action, s32 mods) {
        auto events = static_cast<IEventQueue*>(glfwGetWindowUserPointer(window));
        switch (action) {
            case GLFW_PRESS: {
                events->emplace(IEvent{ IEventType::MouseButtonPressed, button, mods });
            } break;
            case GLFW_RELEASE: {
                events->emplace(IEvent{ IEventType::MouseButtonReleased, button, mods });
            } break;
            default: break;
        }
    });
}

void ContextWindow::initialiseKeyboardEvents()
{
    glfwSetWindowUserPointer(m_window, &m_events);

    glfwSetKeyCallback(m_window, [](GLFWwindow* window, s32 key, s32 /*scancode*/, s32 action, s32 mods) {
        auto events = static_cast<IEventQueue*>(glfwGetWindowUserPointer(window));
        switch (action) {
            case GLFW_PRESS: {
                events->emplace(IEvent{ IEventType::KeyPressed, key, mods });
            } break;
            case GLFW_RELEASE: {
                events->emplace(IEvent{ IEventType::KeyReleased, key, mods });
            } break;
            default: break;
        }
    });
}
