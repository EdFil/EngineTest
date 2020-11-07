#pragma once

#include <cstdint>
#include "window/Utils.hpp"
#include "utils/Size.hpp"
#include "EventDispatcher.hpp"

template<typename T> class EventQueue;
struct SDL_Window;
struct SDL_WindowEvent;

using WindowEventObserver = EventDispatcher<WindowEventType, WindowEvent>::Observer;

class Window {
public:
    Window();
    ~Window();

    bool create(const WindowParams& windowParams);
    void destroy();
    uint32_t id() const;
    Size<int> size() const;
    SDL_Window* sdlWindow() { return _sdlWindow; }
    void OnSDLEvent(const SDL_WindowEvent& event);
    void Subscribe(WindowEventObserver& observer);
    void Unsubscribe(WindowEventObserver& observer);

private:
    EventDispatcher<WindowEventType, WindowEvent> _eventDispatcher;
    SDL_Window* _sdlWindow;
};
