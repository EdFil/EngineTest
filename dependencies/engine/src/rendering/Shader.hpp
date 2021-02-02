#pragma once

#include "core/String.hpp"

class Shader {
public:
    enum class Type { Vertex, Fragment };

    Shader(Type type, const String& source);
    virtual ~Shader();

protected:
    Type _type;
    String _source;
};