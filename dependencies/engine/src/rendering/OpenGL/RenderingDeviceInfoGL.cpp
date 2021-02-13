#include "rendering/OpenGL/RenderingDeviceInfoGL.hpp"

#include <glad/glad.h>

#include "rendering/Types.hpp"

bool RenderingDeviceInfoGL::init() {
    _api = rendering::API::OpenGL;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &_maxVertexAttributes);
    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &_maxTextureSize);
    glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &_maxTextureUnits);
    
    return true;
}

const char* RenderingDeviceInfoGL::vendor() const {
    return (const char*)glGetString(GL_VENDOR);
}

const char* RenderingDeviceInfoGL::renderer() const {
    return (const char*)glGetString(GL_RENDERER);
}

const char* RenderingDeviceInfoGL::version() const {
    return (const char*)glGetString(GL_VERSION);
}