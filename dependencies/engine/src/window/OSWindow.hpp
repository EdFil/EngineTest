#pragma once

#include <cstdint>
#include "window/Utils.hpp"
#include "utils/Size.hpp"
#include "EventDispatcher.hpp"

template<typename T> class EventQueue;
struct SDL_Window;
struct SDL_WindowEvent;

using OSWindowEventObserver = EventDispatcher<OSWindowEventType, OSWindowEvent>::Observer;

class OSWindow {
public:
    OSWindow();
    ~OSWindow();

    bool create(const OSWindowParams& windowParams);
    void destroy();
    uint32_t id() const;
    Size<int> size() const;
    SDL_Window* sdlWindow() { return _sdlWindow; }
    void OnSDLEvent(const SDL_WindowEvent& event);
    void Subscribe(OSWindowEventObserver& observer);
    void Unsubscribe(OSWindowEventObserver& observer);

private:
    EventDispatcher<OSWindowEventType, OSWindowEvent> _eventDispatcher;
    SDL_Window* _sdlWindow;
};
