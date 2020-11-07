#pragma once

#include <cstdint>
#include "utils/Size.hpp"

class OSWindow;
static const unsigned short k_maxWindowCount = 8;

struct OSWindowParams {
    const char* name = "Edgine Window";
    const uint32_t width = 640;
    const uint32_t height = 480;
};

enum class OSWindowEventType { CLOSE, RESIZE };

union OSWindowEventData {
    Size<int> size;
};

struct OSWindowEvent {
    OSWindow& window;
    OSWindowEventData data;
};
