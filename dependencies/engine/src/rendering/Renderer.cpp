#include "rendering/Renderer.hpp"

#include "logger/Logger.hpp"

#include "rendering/Types.hpp"
#include "rendering/OpenGL/RenderingDeviceGL.hpp"

Renderer::Renderer() = default;
Renderer::~Renderer() = default;

bool Renderer::init(SDL_Window* window) {
    _sdlWindow = window;
    if (_sdlWindow == nullptr) {
        LOG_ERROR("[Renderer] Cannot initialize a renderer with an invalid window reference");
        return false;
    }

    setRenderingAPI(rendering::API::OpenGL);

    return _renderingDevice.get() != nullptr;
}

void Renderer::setRenderingAPI(rendering::API renderingAPI) {
    switch (renderingAPI) {
        case rendering::API::OpenGL:
            _renderingDevice = std::make_unique<RenderingDeviceGL>(_sdlWindow);
            break;
        default:
            break;
    }

    _renderingDevice->init();
}