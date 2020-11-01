#pragma once

class Window;

class Renderer {
public:
    Renderer();

    bool initialize(Window* _window);
    void destroy();
    void render();

private:
    bool _isInitialized = false;
    Window* _window;
    unsigned int _width;
    unsigned int _height;
};
