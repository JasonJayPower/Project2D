#include "Graphics/ContextWindow.hpp"

ContextWindow::ContextWindow(const c8* title, s32 w, s32 h)
    : m_window{ createContextWindow(title, w, h) }
{
    initialiseCallbacks();
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
    glfwSetWindowShouldClose(m_window, GLFW_TRUE);
}

bool ContextWindow::pollEvent(IEvent& e)
{
    if (!m_events.empty()) {
        e = std::move(m_events.front());
        m_events.pop();
        return true;
    }
    return false;
}

void ContextWindow::update() const
{
    glfwSwapBuffers(m_window);
    glfwPollEvents();
}

GLFWwindow* ContextWindow::createContextWindow(const c8* title, s32 w, s32 h)
{
    GLFWwindow* window = nullptr;
    window             = glfwCreateWindow(w, h, title, nullptr, nullptr);
    if (window) {
        glfwMakeContextCurrent(window);
        gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
    }
    return window;
}

void ContextWindow::initialiseCallbacks()
{
    glfwSetWindowUserPointer(m_window, &m_events);

    glfwSetKeyCallback(m_window, [](GLFWwindow* window, s32 key, s32 scancode, s32 action, s32 mods) {
        EventQueue* events = static_cast<EventQueue*>(glfwGetWindowUserPointer(window));
        switch (action) {
            case GLFW_PRESS: {
                events->emplace(IEvent{ IEventType::KeyPressed, key, mods });
            } break;
            case GLFW_RELEASE: {
                events->emplace(IEvent{ IEventType::KeyReleased, key, mods });
            } break;
        }
    });
}
