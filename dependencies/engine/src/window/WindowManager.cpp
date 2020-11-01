#include "WindowManager.hpp"

#include <cstdio>
#include <cstring>

#include "Engine.hpp"
#include "SDL.h"

namespace {
    std::unique_ptr<Window> k_nullWindow;
}

WindowManager::WindowManager(Engine& engine) : _engine(engine), _windows{nullptr} {
}

bool WindowManager::initialize() {
#ifdef DEBUG
    SDL_LogSetAllPriority(SDL_LogPriority::SDL_LOG_PRIORITY_DEBUG);
#endif

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("[SDL] Could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    Window* window = createWindow(WindowParams{});
    if (window == nullptr) {
        return false;
    }

    return true;
}

Window* WindowManager::createWindow(const WindowParams& params) {
    size_t i = 0;
    for (; i < k_maxWindowCount; i++) {
        if (_windows[i] == nullptr) break;
    }

    if (i >= k_maxWindowCount) {
        printf("[WindowManager] Error: Already reached the max number of instanced windows (%d)", k_maxWindowCount);
        return nullptr;
    }

    Window* window = new Window(_delayedEventsQueue);
    if (!window->create(params)) {
        delete window;
        return nullptr;
    }

    _windows[i].reset(window);
    return window;
}

void WindowManager::lateUpdate() {
    WindowEvent event;
    while (_delayedEventsQueue.popEvent(event)) {
        switch (event.eventType) {
            case WindowEventType::CLOSE:
                onWindowCloseEvent(event);
                break;
            default:
                break;
        }
    }
}

void WindowManager::destroy() {
    for (size_t i = 0; i < k_maxWindowCount; i++) {
        destroyWindow(_windows[i]);
    }

    SDL_Quit();
}

void WindowManager::OnSDLEvent(const SDL_WindowEvent& event) {
    std::unique_ptr<Window>& windowSlot = windowSlotWithID(event.windowID);
    if (!windowSlot) {
        printf("[WindowManager::OnSDLEvent] Warning: Event window ID did not match any of the windows we have.");
    }

    windowSlot->OnSDLEvent(event);
}

void WindowManager::onWindowCloseEvent(const WindowEvent& event) {
    std::unique_ptr<Window>& window = windowSlotWithID(event.windowID);
    if (!window) {
        printf("[WindowManager::OnSDLEvent] Warning: Event window ID did not match any of the windows we have.");
        return;
    }

    if (window.get() == mainWindow()) {
        _engine.shutdown();
    } else {
        destroyWindow(window);
    }
}

std::unique_ptr<Window>& WindowManager::windowSlotWithID(uint32_t id) {
    for (size_t i = 0; i < k_maxWindowCount; i++) {
        if (_windows[i] && _windows[i]->id() == id) {
            return _windows[i];
        }
    }

    return k_nullWindow;
}

void WindowManager::destroyWindow(std::unique_ptr<Window>& window) {
    if (!window) return;

    window->destroy();
    window.reset();
}