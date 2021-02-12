#include "rendering/OpenGL/RenderingDeviceGL.hpp"

#include <SDL_render.h>
#include <glad/glad.h>
#include <spdlog/spdlog.h>

#include "rendering/OpenGL/ProgramGL.hpp"
#include "rendering/OpenGL/RenderingDeviceInfoGL.hpp"
#include "rendering/OpenGL/ShaderGL.hpp"
#include "rendering/OpenGL/ShaderManagerGL.hpp"

#include "SDL_video.h"

RenderingDeviceGL::RenderingDeviceGL(SDL_Window* window) : _window(window), _context(nullptr) {
}

bool RenderingDeviceGL::init() {
    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);

    _context = SDL_GL_CreateContext(_window);
    if (_context == nullptr) {
        return false;
    }

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        SPDLOG_ERROR("[RenderingDeviceGL] Could not initialize GLAD");
        return false;
    } else {
        SPDLOG_INFO("[RenderingDeviceGL] OpenGL version {}.{}", GLVersion.major, GLVersion.minor);
    }

    bool wasSuccess = true;
    wasSuccess &= _renderingDeviceInfo.init();
    wasSuccess &= _shaderManager.init();

    int width, height;
    SDL_GetWindowSize(_window, &width, &height);
    glViewport(0, 0, width, height);

    return wasSuccess;
}

RenderingDeviceGL::~RenderingDeviceGL() {
    SDL_GL_DeleteContext(_context);
    SDL_DestroyRenderer(_renderer);
}

void RenderingDeviceGL::preRender() {
    static float r = 0;
    static float rDir = 1.0f;
    static float g = 0;
    static float gDir = 1.0f;
    static float b = 0;
    static float bDir = 1.0f;

    r += rand() % 20 == 0 ? 0.01f * rDir : 0.0f;
    g += rand() % 20 == 0 ? 0.01f * gDir : -0.05f;
    b += rand() % 20 == 0 ? 0.01f * bDir : 0.0f;

    (r >= 1.0f) ? rDir = -1.0f : ((r <= 0.0f) ? rDir = 1.0f : (void)0);
    (g >= 1.0f) ? gDir = -1.0f : ((g <= 0.0f) ? gDir = 1.0f : (void)0);
    (b >= 1.0f) ? bDir = -1.0f : ((b <= 0.0f) ? bDir = 1.0f : (void)0);

    glClearColor(r, g, b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void RenderingDeviceGL::postRender() {
    SDL_GL_SwapWindow(_window);
}