#include "rendering/OpenGL/RenderingDeviceGL.hpp"

#include <spdlog/spdlog.h>
#include <GL/glew.h>

#include "rendering/OpenGL/RenderingDeviceInfoGL.hpp"
#include "rendering/OpenGL/ProgramGL.hpp"
#include "rendering/OpenGL/ShaderGL.hpp"
#include "rendering/OpenGL/ShaderManagerGL.hpp"

#include "SDL_video.h"

RenderingDeviceGL::RenderingDeviceGL(SDL_Window* window) : _window(window), _context(nullptr) {
}

bool RenderingDeviceGL::init() {
    _context = SDL_GL_CreateContext(_window);
    if (_context == nullptr) {
        return false;
    }
    
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        SPDLOG_ERROR("[RenderingDeviceGL] Error {}", glewGetErrorString(err));
        return false;
    }

    bool wasSuccess = true;
    wasSuccess &= _renderingDeviceInfo.init();
    wasSuccess &= _shaderManager.init();

    return wasSuccess;
}

RenderingDeviceGL::~RenderingDeviceGL() {
    SDL_GL_DeleteContext(_context);
}