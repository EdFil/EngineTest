#pragma once

#include "OSWindow.hpp"
#include "EventQueue.hpp"
#include "window/Utils.hpp"

class Engine;
struct SDL_WindowEvent;


class OSWindowManager : private OSWindowEventObserver {
public:
    explicit OSWindowManager(Engine& engine);

    bool initialize();
    void onSDLEvent(const SDL_WindowEvent& event);

    OSWindow* createWindow(const OSWindowParams& params);
    OSWindow* mainWindow() const { return _windows[0]; }


private:
    Engine& _engine;
    OSWindow* _windows[k_maxWindowCount];

    void destroy();
    void onWindowClosedEvent(const OSWindowEvent& event);
    OSWindow* windowSlotWithID(uint32_t id);
    void destroyWindow(OSWindow* window);

    void onEventCalled(const OSWindowEventType& type, const OSWindowEvent& data) final;
};
