#pragma once

#include <memory>
#include <vector>

#include "EventQueue.hpp"
#include "window/OSWindowManager.hpp"
#include "rendering/Renderer.hpp"

class Engine {
public:
    Engine(int argc, char* argv[]);
    Engine(const Engine& rhs) = delete;
    Engine(const Engine&& rhs) = delete;
    Engine& operator=(const Engine& rhs) = delete;
    Engine& operator=(const Engine&& rhs) = delete;

    bool initialize();
    void run();
    void shutdown();

private:
    void mainLoop();

private:
    OSWindowManager _windowManager;
    Renderer _renderer;

    unsigned _lastGetTicksTime = 0;

    bool _isRunning = false;
};