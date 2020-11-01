#pragma once

#include <cstdint>
#include "window/Utils.hpp"
#include "utils/Size.hpp"

template<typename T> class EventDispatcher;
struct SDL_Window;
struct SDL_WindowEvent;

class Window {
public:
    Window(EventDispatcher<WindowEvent>& engine);
    ~Window();

    bool create(const WindowParams& windowParams);
    void destroy();
    uint32_t id() const;
    Size<int> size() const;
    SDL_Window* sdlWindow() { return _sdlWindow; }
    void OnSDLEvent(const SDL_WindowEvent& event);

private:
    EventDispatcher<WindowEvent>& _eventDispatcher;
    SDL_Window* _sdlWindow;
};
