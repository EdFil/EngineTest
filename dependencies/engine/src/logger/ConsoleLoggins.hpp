#include "ILogger.hpp"

class TerminalLogger final : public ILogger {
public:
    bool init() override { return true; }
    void print(const char* message) override { printf("%s", message); }
};