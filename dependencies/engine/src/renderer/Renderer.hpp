#pragma once

#include "window/Window.hpp"

class Renderer : private WindowEventObserver {
public:
    Renderer();

    bool initialize(Window* _window);
    void destroy();
    void render();

    void onEventCalled(const WindowEventType& type, const WindowEvent& event) override;

private:
    bool _isInitialized = false;
    Window* _window;
    unsigned int _width;
    unsigned int _height;

};
