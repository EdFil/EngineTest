#include "rendering/OpenGL/ProgramGL.hpp"

#include <GL/glew.h>
#include <spdlog/spdlog.h>
#include "rendering/RenderingDevice.hpp"
#include "rendering/OpenGL/ShaderGL.hpp"

ProgramGL::ProgramGL(const String& vertexShader, const String& fragmentShader) : Program(vertexShader, fragmentShader) {
    
}

ProgramGL::~ProgramGL() {
}

void ProgramGL::createProgram(Device& device) {
    //_vertexShader = (ShaderGL*)device.createShader(Shader::Type::Vertex, _vertexShaderSource);
    //_fragmentShader = (ShaderGL*)device.createShader(Shader::Type::Fragment, _fragmentShaderSource);

    //_id = glCreateProgram();
    //if (_id == 0) {
    //    SPDLOG_ERROR("Error creating program");
    //    return;
    //}

    //glAttachShader(_id, _vertexShader->id());
    //glAttachShader(_id, _fragmentShader->id());
    //glLinkProgram(_id);

    //GLint status = 0;
    //glGetProgramiv(_id, GL_LINK_STATUS, &status);
    //if (GL_FALSE == status) {
    //    SPDLOG_ERROR("{}: failed to link program");
    //    deleteProgram();
    //}
}

void ProgramGL::deleteProgram() {
    if (_id) {
        glDeleteProgram(_id);
        _id = 0;
    }
}