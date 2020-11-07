#pragma once

#include "utils/Size.hpp"
#include "EventDispatcher.hpp"

enum class OSWindowEventType { CLOSE, RESIZE };

union OSWindowEventData {
    Size<int> size;
};

class OSWindow;
struct OSWindowEvent {
    OSWindow& window;
    OSWindowEventData data;
};

using OSWindowEventObserver = EventDispatcher<OSWindowEventType, OSWindowEvent>::Observer;