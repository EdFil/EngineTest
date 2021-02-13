#include "Engine.hpp"

#include <backends/imgui_impl_sdl.h>
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
            ImGui_ImplSDL2_ProcessEvent(&sdlEvent);

            // User requests quit
            if (sdlEvent.type == SDL_QUIT) {
                shutdown();
            } else if (sdlEvent.type == SDL_WINDOWEVENT) {
                _windowManager.onSDLEvent(sdlEvent.window);
            }
        }

        _renderer.renderingDevice()->preRender();

        {
            static bool show_demo_window = true;
            static bool show_another_window = false;
            static float clear_color[3];
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Hello, world!");  // Create a window called "Hello, world!" and append into it.

            ImGui::Text("This is some useful text.");           // Display some text (you can use a format strings too) 
            ImGui::Checkbox("Demo Window", &show_demo_window);  // Edit bools storing our window open/close state 
            ImGui::Checkbox("Another Window", &show_another_window);

            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);             // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::ColorEdit3("clear color", (float*)&clear_color);  // Edit 3 floats representing a color

            if (ImGui::Button("Button"))  // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate,
                        ImGui::GetIO().Framerate);
            ImGui::End();
        }

        ImGui::Render();
        _renderer.renderingDevice()->postRender();
    }
}

void Engine::shutdown() {
    _isRunning = false;
}
