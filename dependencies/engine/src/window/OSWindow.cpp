#include "OSWindow.hpp"

#include "spdlog/spdlog.h"
#include "SDL_events.h"
#include "SDL_video.h"

const char* stringifyWindowEventID(SDL_WindowEventID eventID) {
    switch (eventID) {
        case SDL_WINDOWEVENT_NONE:
            return "SDL_WINDOWEVENT_NONE";
        case SDL_WINDOWEVENT_SHOWN:
            return "SDL_WINDOWEVENT_SHOWN";
        case SDL_WINDOWEVENT_HIDDEN:
            return "SDL_WINDOWEVENT_HIDDEN";
        case SDL_WINDOWEVENT_EXPOSED:
            return "SDL_WINDOWEVENT_EXPOSED";
        case SDL_WINDOWEVENT_MOVED:
            return "SDL_WINDOWEVENT_MOVED";
        case SDL_WINDOWEVENT_RESIZED:
            return "SDL_WINDOWEVENT_RESIZED";
        case SDL_WINDOWEVENT_SIZE_CHANGED:
            return "SDL_WINDOWEVENT_SIZE_CHANGED";
        case SDL_WINDOWEVENT_MINIMIZED:
            return "SDL_WINDOWEVENT_MINIMIZED";
        case SDL_WINDOWEVENT_MAXIMIZED:
            return "SDL_WINDOWEVENT_MAXIMIZED";
        case SDL_WINDOWEVENT_RESTORED:
            return "SDL_WINDOWEVENT_RESTORED";
        case SDL_WINDOWEVENT_ENTER:
            return "SDL_WINDOWEVENT_ENTER";
        case SDL_WINDOWEVENT_LEAVE:
            return "SDL_WINDOWEVENT_LEAVE";
        case SDL_WINDOWEVENT_FOCUS_GAINED:
            return "SDL_WINDOWEVENT_FOCUS_GAINED";
        case SDL_WINDOWEVENT_FOCUS_LOST:
            return "SDL_WINDOWEVENT_FOCUS_LOST";
        case SDL_WINDOWEVENT_CLOSE:
            return "SDL_WINDOWEVENT_CLOSE";
        case SDL_WINDOWEVENT_TAKE_FOCUS:
            return "SDL_WINDOWEVENT_TAKE_FOCUS";
        case SDL_WINDOWEVENT_HIT_TEST:
            return "SDL_WINDOWEVENT_HIT_TEST";
        default:
            return "ERROR";
    }
}

OSWindow::OSWindow() : _sdlWindow(nullptr) {
}

OSWindow::~OSWindow() {
    destroy();
}

bool OSWindow::create(const OSWindowParams& params) {
    if (_sdlWindow != nullptr) {
        spdlog::warn("[OSWindow] Already initialized. Skipping...");
        return true;
    }

    // Create OSWindow
    _sdlWindow = SDL_CreateWindow(params.name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, params.width,
                                  params.height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
    if (_sdlWindow == nullptr) {
        spdlog::error("[SDL] Could not create a SDL OSWindow. {}", SDL_GetError());
        return false;
    }

    return true;
}

void OSWindow::onSDLEvent(const SDL_WindowEvent& event) {
    SDL_WindowEventID windowEventID = (SDL_WindowEventID)event.event;
    spdlog::debug("[OSWindow({})::onSDLEvent] {}\n", id(), stringifyWindowEventID(windowEventID));

    OSWindowEvent windowEvent{*this, {}};
    switch (windowEventID) {
        case SDL_WINDOWEVENT_CLOSE:
            _eventDispatcher.Signal(OSWindowEventType::CLOSE, windowEvent);
            break;

        case SDL_WINDOWEVENT_RESIZED:
            windowEvent.data.size = {event.data1, event.data2};
            _eventDispatcher.Signal(OSWindowEventType::RESIZE, windowEvent);
            break;

        case SDL_WINDOWEVENT_NONE:
        case SDL_WINDOWEVENT_SHOWN:
        case SDL_WINDOWEVENT_HIDDEN:
        case SDL_WINDOWEVENT_EXPOSED:
        case SDL_WINDOWEVENT_MOVED:
        case SDL_WINDOWEVENT_SIZE_CHANGED:
        case SDL_WINDOWEVENT_MINIMIZED:
        case SDL_WINDOWEVENT_MAXIMIZED:
        case SDL_WINDOWEVENT_RESTORED:
        case SDL_WINDOWEVENT_ENTER:
        case SDL_WINDOWEVENT_LEAVE:
        case SDL_WINDOWEVENT_FOCUS_GAINED:
        case SDL_WINDOWEVENT_FOCUS_LOST:
        case SDL_WINDOWEVENT_TAKE_FOCUS:
        case SDL_WINDOWEVENT_HIT_TEST:
            break;
    }
}

uint32_t OSWindow::id() const {
    return SDL_GetWindowID(_sdlWindow);
}

Size<int> OSWindow::size() const {
    Size<int> size;
    SDL_GetWindowSize(_sdlWindow, &size.width, &size.height);
    return size;
}

void OSWindow::destroy() {
    if (_sdlWindow == nullptr) {
        spdlog::warn("[OSWindow] Trying to destroy OSWindow when it's not created");
        return;
    }

    SDL_DestroyWindow(_sdlWindow);
    _sdlWindow = nullptr;
}

void OSWindow::subscribe(OSWindowEventObserver& observer) {
    _eventDispatcher.Subscribe(observer);
}

void OSWindow::unsubscribe(OSWindowEventObserver& observer) {
    _eventDispatcher.Unsubscribe(observer);
}