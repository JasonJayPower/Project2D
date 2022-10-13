#include "Input/EventHandler.hpp"

void EventHandler::handleEvent(IEvent e)
{
    for (const auto& binding : m_keyBindings) {
        if (e.type == binding.second.type) {
            switch (e.type) {
                case IEventType::KeyPressed:
                case IEventType::KeyReleased: {
                    if (e.data.keyboard.key == binding.second.data.keyboard.key) {
                        callback(binding.first, binding.second.data);
                    }
                } break;
                //case IEventType::MouseButtonPressed:
                //case IEventType::MouseButtonReleased: {
                //    if (e.data.mouse.btn == binding.second.data.mouse.btn) {
                //        callback(binding.first, binding.second.data);
                //    }
                //} break;
                //case IEventType::WindowResize:
                //case IEventType::MouseMoved: {
                //    callback(binding.first, e.data);
                //} break;
                default: break;
            }
        }
    }
}

void EventHandler::addCallback(IEventAction action, IEventCallback callback)
{
    m_callbacks.try_emplace(action, callback);
}

void EventHandler::callback(IEventAction action, IEventData data) const
{
    if (const auto it = m_callbacks.find(action); it != m_callbacks.end()) {
        it->second(data);
    }
}
