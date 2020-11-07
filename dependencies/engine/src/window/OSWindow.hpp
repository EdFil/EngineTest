#pragma once

#include <cstdint>
#include "window/Utils.hpp"
#include "utils/Size.hpp"
#include "EventDispatcher.hpp"
#include "window/OSWindowEvent.h"

struct SDL_Window;
struct SDL_WindowEvent;

class OSWindow {
public:
    OSWindow();
    ~OSWindow();

    bool create(const OSWindowParams& windowParams);
    void destroy();
    uint32_t id() const;
    Size<int> size() const;
    SDL_Window* sdlWindow() { return _sdlWindow; }
    void onSDLEvent(const SDL_WindowEvent& event);
    void subscribe(OSWindowEventObserver& observer);
    void unsubscribe(OSWindowEventObserver& observer);

private:
    EventDispatcher<OSWindowEventType, OSWindowEvent> _eventDispatcher;
    SDL_Window* _sdlWindow;
};
