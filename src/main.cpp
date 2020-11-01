#include <Engine.hpp>

int main(int argc, char* argv[]) {
    Engine engine(argc, argv);
    engine.initialize();
    engine.run();
    return 0;
}