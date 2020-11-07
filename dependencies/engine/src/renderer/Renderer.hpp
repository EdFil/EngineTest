#pragma once

#include "window/OSWindow.hpp"

class Renderer : private OSWindowEventObserver {
public:
    Renderer();

    bool initialize(OSWindow* _window);
    void destroy();
    void render();

    void onEventCalled(const OSWindowEventType& type, const OSWindowEvent& event) override;

private:
    bool _isInitialized = false;
    OSWindow* _window;
    unsigned int _width;
    unsigned int _height;

};
