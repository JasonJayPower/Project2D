#pragma once
#include <queue>

#include "Utils/Delegate.hpp"
#include "Utils/Types.hpp"

namespace Input {
    enum class Action { None, MousePos, Quit, Up, Down, Left, Right, BtnA, BtnB };

    enum class EventType {
        None = 0,
        KeyPressed,
        KeyReleased,
        MouseButtonPressed,
        MouseButtonReleased,
        MouseMoved,
        WindowResize
    };
    struct WindowResizeEvent {
        s32 w = 0;
        s32 h = 0;
    };

    struct KeyboardEvent {
        s32 key = 0;
        s32 mod = 0;
    };

    struct MouseBtnEvent {
        s32 btn = 0;
        s32 mod = 0;
    };

    struct MousePosition {
        s32 x = 0;
        s32 y = 0;
    };

    struct EventData {
        union {
            WindowResizeEvent windowSize;
            KeyboardEvent keyboard;
            MouseBtnEvent mouse;
            MousePosition mousePos;
        };
    };

    struct Event {
        EventType type = EventType::None;
        EventData data = { 0, 0 };
    };
}  // namespace Input
using IEvent         = Input::Event;
using IEventAction   = Input::Action;
using IEventData     = Input::EventData;
using IEventType     = Input::EventType;
using IEventQueue    = std::queue<IEvent>;
using IEventCallback = Delegate<void(IEventData)>;
