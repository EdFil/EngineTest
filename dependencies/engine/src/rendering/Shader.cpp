#include "rendering/Shader.hpp"

Shader::Shader(Type type, const String& source) : _type(type), _source(source) {
}

Shader::~Shader() = default;