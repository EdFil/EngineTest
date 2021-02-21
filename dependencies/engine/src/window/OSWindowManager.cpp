#include "OSWindowManager.hpp"

#include <SDL.h>
#include <cstring>

#include "Engine.hpp"
#include "logger/Logger.hpp"

OSWindowManager::OSWindowManager(Engine& engine) : _engine(engine) {
}

bool OSWindowManager::initialize() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        LOG_ERROR("[OSWindowManager] Could not initialize! SDL_Error: %s", SDL_GetError());
        return false;
    }

    OSWindow* window = createWindow(OSWindowParams{});
    if (window == nullptr) {
        LOG_ERROR("[OSWindowManager] Could not create main window");
        return false;
    }

    return true;
}

OSWindow* OSWindowManager::createWindow(const OSWindowParams& params) {
    if (_windows.size() == _windows.capacity()) {
        LOG_ERROR("[OSWindowManager] Error: Already reached the max number of instanced windows (%d)",
                  _windows.capacity());
        return nullptr;
    }

    OSWindow* window = _windows.emplace_back();
    if (!window->create(params)) {
        destroyWindow(window);
        return nullptr;
    }

    return window;
}

void OSWindowManager::destroyWindow(OSWindow* window) {
    _windows.erase(std::remove(_windows.begin(), _windows.end(), *window));
}

void OSWindowManager::onEventCalled(const OSWindowEventType& type, const OSWindowEvent& data) {
    switch (type) {
        case OSWindowEventType::CLOSE:
            onWindowClosedEvent(data);
            break;
        default:
            break;
    }
}

void OSWindowManager::destroy() {
    for (uint32_t i = _windows.size() - 1; i > 0; --i) {
        destroyWindow(&_windows[i]);
    }
}

void OSWindowManager::onSDLEvent(const SDL_WindowEvent& event) {
    OSWindow* windowSlot = windowSlotWithID(event.windowID);
    if (windowSlot == nullptr) {
        LOG_ERROR("[OSWindowManager::onSDLEvent] Event window ID did not match any of the windows we have.");
        return;
    }

    windowSlot->onSDLEvent(event);
}

void OSWindowManager::onWindowClosedEvent(const OSWindowEvent& event) {
    OSWindow* window = windowSlotWithID(event.window.id());
    if (window == nullptr) {
        LOG_ERROR("[OSWindowManager::onSDLEvent] Event window ID did not match any of the windows we have.");
        return;
    }

    if (window == mainWindow()) {
        _engine.shutdown();
    } else {
        destroyWindow(window);
    }
}

OSWindow* OSWindowManager::windowSlotWithID(uint32_t id) {
    for (uint32_t i = 0; i < _windows.size(); ++i) {
        if (_windows[i].id() == id) {
            return &_windows[i];
        }
    }

    return nullptr;
}