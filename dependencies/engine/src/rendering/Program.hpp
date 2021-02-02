#pragma once

#include "core/String.hpp"

class Program {
public:
    Program(const String& vertexShader, const String& fragmentShader);
    virtual ~Program();

protected:
    String _vertexShaderSource;
    String _fragmentShaderSource;
};