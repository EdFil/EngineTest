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

    bool isValid() const { return m_pSDLWindow == nullptr; }
    uint32_t id() const;
    Size<int> size() const;
    SDL_Window* sdlWindow() { return m_pSDLWindow; }

    void onSDLEvent(const SDL_WindowEvent& event);
    void subscribe(OSWindowEventObserver& observer);
    void unsubscribe(OSWindowEventObserver& observer);
    bool operator==(const OSWindow& window) const { return m_pSDLWindow == window.m_pSDLWindow; }

private:
    EventDispatcher<OSWindowEventType, OSWindowEvent> m_eventDispatcher;
    SDL_Window* m_pSDLWindow = nullptr;
};
