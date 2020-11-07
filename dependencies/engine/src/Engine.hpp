#pragma once

#include <memory>
#include <vector>

#include <flecs.h>

#include "window/OSWindowManager.hpp"
#include "renderer/Renderer.hpp"
#include "EventQueue.hpp"

struct SDL_Window;
struct SDL_Renderer;
class Scene;

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
    flecs::world _world;

    bool _isRunning = false;
};