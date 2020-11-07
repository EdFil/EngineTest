#pragma once

#include <cstdint>
#include "utils/Size.hpp"

class Window;
static const unsigned short k_maxWindowCount = 8;

struct WindowParams {
    const char* name = "Edgine Window";
    const uint32_t width = 640;
    const uint32_t height = 480;
};

enum class WindowEventType { CLOSE, RESIZE };

union WindowEventData {
    Size<int> size;
};

struct WindowEvent {
    WindowEvent() = default;

    Window& window;
    WindowEventData data;
};
