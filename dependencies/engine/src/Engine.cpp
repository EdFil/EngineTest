#include "Engine.hpp"

#include <cstdlib>
#include <ctime>

#include "SDL.h"
#include "TextureManager.hpp"
#include "logger/Logger.hpp"
#include "rendering/RenderingDevice.hpp"

Engine::Engine(int argc, char* argv[]) : _windowManager(*this) {
}

bool Engine::initialize() {
    if (!Logger::init()) return false;
    if (!_windowManager.initialize()) return false;
    if (!_renderer.init(_windowManager.mainWindow()->sdlWindow())) return false;

    return true;
}

void Engine::run() {
    _isRunning = true;
    // _lastGetTicksTime = SDL_GetTicks();
    mainLoop();
}

void Engine::mainLoop() {
    while (_isRunning) {
        const unsigned currentTime = SDL_GetTicks();
        float delta = static_cast<float>(currentTime - _lastGetTicksTime) / 1000.0f;
        (void)delta;
        _lastGetTicksTime = currentTime;

        SDL_Event sdlEvent;
        while (SDL_PollEvent(&sdlEvent) != 0) {
            // User requests quit
            if (sdlEvent.type == SDL_QUIT) {
                shutdown();
            } else if (sdlEvent.type == SDL_WINDOWEVENT) {
                _windowManager.onSDLEvent(sdlEvent.window);
            }
        }

        _renderer.renderingDevice()->preRender();
        _renderer.renderingDevice()->postRender();
    }
}

void Engine::shutdown() {
    _isRunning = false;
}
