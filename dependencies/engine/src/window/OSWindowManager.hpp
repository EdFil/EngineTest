#pragma once

#include <memory>

#include "OSWindow.hpp"
#include "EventQueue.hpp"
#include "window/Utils.hpp"

class Engine;
struct SDL_WindowEvent;


class OSWindowManager : private OSWindowEventObserver {
public:
    OSWindowManager(Engine& engine);

    bool initialize();
    void OnSDLEvent(const SDL_WindowEvent& event);

    OSWindow* createWindow(const OSWindowParams& params);
    OSWindow* mainWindow() const { return _windows[0].get(); }


private:
    Engine& _engine;
    std::unique_ptr<OSWindow> _windows[k_maxWindowCount];

    void destroy();
    void onWindowClosedEvent(const OSWindowEvent& event);
    std::unique_ptr<OSWindow>& windowSlotWithID(uint32_t id);
    void destroyWindow(std::unique_ptr<OSWindow>& window);

    void onEventCalled(const OSWindowEventType& type, const OSWindowEvent& data);
};
