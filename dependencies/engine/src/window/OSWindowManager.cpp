#include "OSWindowManager.hpp"

#include <cstdio>
#include <cstring>

#include "Engine.hpp"
#include "SDL.h"

namespace {
    std::unique_ptr<OSWindow> k_nullWindow;
}

OSWindowManager::OSWindowManager(Engine& engine) : _engine(engine), _windows{nullptr} {
}

bool OSWindowManager::initialize() {
#ifdef DEBUG
    SDL_LogSetAllPriority(SDL_LogPriority::SDL_LOG_PRIORITY_DEBUG);
#endif

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("[SDL] Could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    OSWindow* window = createWindow(OSWindowParams{});
    if (window == nullptr) {
        return false;
    }

    return true;
}

OSWindow* OSWindowManager::createWindow(const OSWindowParams& params) {
    size_t i = 0;
    for (; i < k_maxWindowCount; i++) {
        if (_windows[i] == nullptr) break;
    }

    if (i >= k_maxWindowCount) {
        printf("[OSWindowManager] Error: Already reached the max number of instanced windows (%d)", k_maxWindowCount);
        return nullptr;
    }

    OSWindow* window = new OSWindow();
    if (!window->create(params)) {
        delete window;
        return nullptr;
    }

    _windows[i].reset(window);
    return window;
}

void OSWindowManager::onEventCalled(const OSWindowEventType& type, const OSWindowEvent& data) {
    switch (type) {
        case OSWindowEventType::CLOSE:
            onWindowClosedEvent(data);
        default:
            break;
    }
}

void OSWindowManager::destroy() {
    for (size_t i = 0; i < k_maxWindowCount; i++) {
        destroyWindow(_windows[i]);
    }

    SDL_Quit();
}

void OSWindowManager::OnSDLEvent(const SDL_WindowEvent& event) {
    std::unique_ptr<OSWindow>& windowSlot = windowSlotWithID(event.windowID);
    if (!windowSlot) {
        printf("[OSWindowManager::OnSDLEvent] Warning: Event window ID did not match any of the windows we have.");
    }

    windowSlot->OnSDLEvent(event);
}

void OSWindowManager::onWindowClosedEvent(const OSWindowEvent& event) {
    std::unique_ptr<OSWindow>& window = windowSlotWithID(event.window.id());
    if (!window) {
        printf("[OSWindowManager::OnSDLEvent] Warning: Event window ID did not match any of the windows we have.");
        return;
    }

    if (window.get() == mainWindow()) {
        _engine.shutdown();
    } else {
        destroyWindow(window);
    }
}

std::unique_ptr<OSWindow>& OSWindowManager::windowSlotWithID(uint32_t id) {
    for (size_t i = 0; i < k_maxWindowCount; i++) {
        if (_windows[i] && _windows[i]->id() == id) {
            return _windows[i];
        }
    }

    return k_nullWindow;
}

void OSWindowManager::destroyWindow(std::unique_ptr<OSWindow>& window) {
    if (!window) return;

    window->destroy();
    window.reset();
}