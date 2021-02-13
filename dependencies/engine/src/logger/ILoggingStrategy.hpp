#pragma once

class ILogger {
public:
    virtual ~ILogger() = default;
    virtual bool init() = 0;
    virtual void print(const char* message) = 0;
};
