#pragma once

#include <memory>

#include "Window.hpp"
#include "EventQueue.hpp"
#include "window/Utils.hpp"

class Engine;
struct SDL_WindowEvent;


class WindowManager : private WindowEventObserver {
public:
    WindowManager(Engine& engine);

    bool initialize();
    void OnSDLEvent(const SDL_WindowEvent& event);
    
    Window* createWindow(const WindowParams& params);
    Window* mainWindow() const { return _windows[0].get(); }


private:
    Engine& _engine;
    std::unique_ptr<Window> _windows[k_maxWindowCount];

    void destroy();
    void onWindowClosedEvent(const WindowEvent& event);
    std::unique_ptr<Window>& windowSlotWithID(uint32_t id);
    void destroyWindow(std::unique_ptr<Window>& window);

    void onEventCalled(const WindowEventType& type, const WindowEvent& data);
};
