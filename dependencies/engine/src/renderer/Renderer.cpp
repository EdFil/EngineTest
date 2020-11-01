#include "renderer/Renderer.hpp"

#include <cstdio>

#include "window/Window.hpp"
#include "bgfx/platform.h"
#include "SDL_syswm.h"

Renderer::Renderer() : _window(nullptr) {
}

bool Renderer::initialize(Window* window) {
    if (window == nullptr) {
        printf("[Renderer] Error: Invalid window, cannot initialize.");
        return false;
    }

    _window = window;
    Size<int> size = _window->size();
    _width = size.width;
    _height = size.height;

    // Associate this window with BGFX
    SDL_SysWMinfo wmi;
    SDL_VERSION(&wmi.version);
    if (!SDL_GetWindowWMInfo(_window->sdlWindow(), &wmi)) {
        return false;
    }

    bgfx::PlatformData pd;
#if BX_PLATFORM_LINUX || BX_PLATFORM_BSD
    pd.ndt = wmi.info.x11.display;
    pd.nwh = (void*)(uintptr_t)wmi.info.x11.window;
#elif BX_PLATFORM_OSX
    pd.nwh = wmi.info.cocoa.window;
#elif BX_PLATFORM_WINDOWS
    pd.nwh = wmi.info.win.window;
#elif BX_PLATFORM_STEAMLINK
    pd.ndt = wmi.info.vivante.display;
    pd.nwh = wmi.info.vivante.window;
#endif  // BX_PLATFORM_
    //bgfx::setPlatformData(pd);


    // Init bgfx
    bgfx::Init init;
    init.platformData = pd;
    init.type = bgfx::RendererType::OpenGL;
    if (!bgfx::init(init)) {
        return false;
    }

    bgfx::reset(_width, _height, BGFX_RESET_VSYNC);
    bgfx::setDebug(BGFX_DEBUG_TEXT);
    _isInitialized = true;

    // Set view 0 default viewport.
    bgfx::setViewRect(0, 0, 0, uint16_t(_width), uint16_t(_height));

    bgfx::touch(0);

    return true;
}

void Renderer::destroy() {
    if (_isInitialized) {
        bgfx::shutdown();
        _isInitialized = false;
    }
}

void Renderer::render() {

    bgfx::setViewClear(0, BGFX_CLEAR_COLOR, 0x000000FF);

    // Use debug font to print information about this example.
    bgfx::dbgTextClear();
   
    bgfx::dbgTextPrintf(
        0, 1, 0x0f,
        "Color can be changed with ANSI \x1b[9;me\x1b[10;ms\x1b[11;mc\x1b[12;ma\x1b[13;mp\x1b[14;me\x1b[0m code too.");

    bgfx::dbgTextPrintf(80, 1, 0x0f,
                        "\x1b[;0m    \x1b[;1m    \x1b[; 2m    \x1b[; 3m    \x1b[; 4m    \x1b[; 5m    \x1b[; 6m    "
                        "\x1b[; 7m    \x1b[0m");
    bgfx::dbgTextPrintf(80, 2, 0x0f,
                        "\x1b[;8m    \x1b[;9m    \x1b[;10m    \x1b[;11m    \x1b[;12m    \x1b[;13m    \x1b[;14m    "
                        "\x1b[;15m    \x1b[0m");

    const bgfx::Stats* stats = bgfx::getStats();
    bgfx::dbgTextPrintf(0, 2, 0x0f, "Backbuffer %dW x %dH in pixels, debug text %dW x %dH in characters.", stats->width,
                        stats->height, stats->textWidth, stats->textHeight);

    // Advance to next frame. Rendering thread will be kicked to
    // process submitted rendering primitives.
    bgfx::frame();
}