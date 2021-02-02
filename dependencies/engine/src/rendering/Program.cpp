#include "rendering/Program.hpp"

Program::Program(const String& vertexShader, const String& fragmentShader)
  : _vertexShaderSource(vertexShader), _fragmentShaderSource(fragmentShader) {
}

Program::~Program() = default;