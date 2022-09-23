#pragma once

#include "Utils/Types.hpp"

namespace Input {
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

	struct MouseMovedEvent {
		s32 x = 0;
		s32 y = 0;
	};

	struct MouseEvent {
		s32 btn = 0;
		s32 mod = 0;
	};

	struct Event {
		EventType type;
		union {
			WindowResizeEvent windowSize;
			KeyboardEvent     keyboard;
			MouseEvent        mouse;
			MouseMovedEvent   mouseMove;
		};
	};
}

using IEvent     = Input::Event;
using IEventType = Input::EventType;
