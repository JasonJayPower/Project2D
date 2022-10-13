#pragma once

#include <unordered_map>

#include "Input/Types.hpp"
#include "Utils/Delegate.hpp"

class EventHandler
{
    using Callbacks   = std::unordered_map<IEventAction, IEventCallback>;
    using KeyBindings = std::unordered_map<IEventAction, IEvent>;

  public:
    void handleEvent(IEvent e);

    void addCallback(IEventAction action, IEventCallback callback);

    void callback(IEventAction action, IEventData data) const;

  private:
    Callbacks m_callbacks;
    KeyBindings m_keyBindings{
        { IEventAction::Up,    { IEventType::KeyPressed, { 87, 0 } } },
        { IEventAction::Down,  { IEventType::KeyPressed, { 83, 0 } } },
        { IEventAction::Left,  { IEventType::KeyPressed, { 65, 0 } } },
        { IEventAction::Right, { IEventType::KeyPressed, { 68, 0 } } },
    };
};
