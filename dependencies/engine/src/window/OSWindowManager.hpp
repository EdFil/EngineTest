#pragma once

#include "OSWindow.hpp"
#include "container/FixedArray.hpp"
#include "window/Utils.hpp"

class Engine;
struct SDL_WindowEvent;

class OSWindowManager : private OSWindowEventObserver {
public:
    explicit OSWindowManager(Engine& engine);

    bool initialize();
    void onSDLEvent(const SDL_WindowEvent& event);

    OSWindow* createWindow(const OSWindowParams& params);
    void destroyWindow(OSWindow* window);
    OSWindow* mainWindow() { return _windows.begin(); }

private:
    Engine& _engine;
    FixedArray<OSWindow, k_maxWindowCount> _windows;

    void destroy();
    void onWindowClosedEvent(const OSWindowEvent& event);
    OSWindow* windowSlotWithID(uint32_t id);

    void onEventCalled(const OSWindowEventType& type, const OSWindowEvent& data) final;
};
