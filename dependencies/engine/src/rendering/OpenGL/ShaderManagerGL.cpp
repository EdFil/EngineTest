#include "rendering/OpenGL/ShaderManagerGL.hpp"

#include <GL/glew.h>

#include "rendering/OpenGL/ShaderGL.hpp"

ShaderManagerGL::~ShaderManagerGL() {

}

bool ShaderManagerGL::init() {
    return true;
}

Shader* ShaderManagerGL::createShader(Shader::Type type, const String& source) {
    return nullptr;
}