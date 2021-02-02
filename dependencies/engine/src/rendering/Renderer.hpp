#pragma once

#include <memory>

struct SDL_Window;
class RenderingDevice;
namespace rendering {
enum class API;
}

class Renderer {
public:
    Renderer();
    ~Renderer();

    bool init(SDL_Window* window);

    RenderingDevice* renderingDevice() const { return _renderingDevice.get(); }
    void setRenderingAPI(rendering::API renderingAPI);

private:
    SDL_Window* _sdlWindow;
    std::unique_ptr<RenderingDevice> _renderingDevice;
};
