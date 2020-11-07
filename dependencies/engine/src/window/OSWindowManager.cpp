#include "OSWindowManager.hpp"

#include <cstring>

#include "spdlog/spdlog.h"
#include "SDL.h"
#include "Engine.hpp"

OSWindowManager::OSWindowManager(Engine& engine) : _engine(engine), _windows{nullptr} {
}

bool OSWindowManager::initialize() {
#ifdef DEBUG
    SDL_LogSetAllPriority(SDL_LogPriority::SDL_LOG_PRIORITY_DEBUG);
#endif

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        spdlog::error("[SDL] Could not initialize! SDL_Error: {}", SDL_GetError());
        return false;
    }

    OSWindow* window = createWindow(OSWindowParams{});
    if (window == nullptr) {
        spdlog::error("[OSWindowManager] Could not create main window");
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
        spdlog::error("[OSWindowManager] Error: Already reached the max number of instanced windows ({})", k_maxWindowCount);
        return nullptr;
    }

    OSWindow* window = new OSWindow();
    if (!window->create(params)) {
        delete window;
        return nullptr;
    }

    _windows[i] = window;
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

void OSWindowManager::onSDLEvent(const SDL_WindowEvent& event) {
    OSWindow* windowSlot = windowSlotWithID(event.windowID);
    if (windowSlot == nullptr) {
        spdlog::warn("[OSWindowManager::onSDLEvent] Event window ID did not match any of the windows we have.");
        return;
    }

    windowSlot->onSDLEvent(event);
}

void OSWindowManager::onWindowClosedEvent(const OSWindowEvent& event) {
    OSWindow* window = windowSlotWithID(event.window.id());
    if (window == nullptr) {
        spdlog::warn("[OSWindowManager::onSDLEvent] Event window ID did not match any of the windows we have.");
        return;
    }

    if (window == mainWindow()) {
        _engine.shutdown();
    } else {
        destroyWindow(window);
    }
}

OSWindow* OSWindowManager::windowSlotWithID(uint32_t id) {
    for (size_t i = 0; i < k_maxWindowCount; i++) {
        if (_windows[i] && _windows[i]->id() == id) {
            return _windows[i];
        }
    }

    return nullptr;
}

void OSWindowManager::destroyWindow(OSWindow* window) {
    size_t i = 0;
    for (; i < k_maxWindowCount; i++) {
        if (_windows[i] == window) break;
    }

    if (i < k_maxWindowCount && _windows[i] != nullptr) {
        delete _windows[i];
        _windows[i] = nullptr;
    }
}