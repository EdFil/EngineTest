#include "ILogger.hpp"

#include <ostream>
#include <fstream>

namespace {
const char* k_loggerFileName = "log.log";
}

class FileLogger final : public ILogger {
public:
    bool init() override {
        _logFile.open(k_loggerFileName);
        return _logFile.is_open();
    }

    void print(const char* message) override { printf("%s", message); }

private:
    std::ofstream _logFile;
};