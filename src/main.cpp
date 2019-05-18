#include <chrono>
#include "ecs/TransformSystem.h"


#define BENCHMARK(__PARAM__) \
{\
    auto start = std::chrono::high_resolution_clock::now();\
    __PARAM__\
    auto elapsed =  std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now() - start);\
    std::cout << "[TIME] Took "<< elapsed.count() << " stuffs" << std::endl;\
}

int main() {
    TransformSystem system;
    system.initWithCapacity(100);

    const size_t phase1 = 99;
    GlobalHandle phase1Handles[phase1];
    for (size_t i = 0; i < phase1; i++) {
        phase1Handles[i] = system.createComponent();
    }

    system.createComponent();
    system.createComponent();

    const size_t phase2 = 3;
    GlobalHandle phase2Handles[phase2] = { phase1Handles[12], phase1Handles[1], phase1Handles[30]};
    for (size_t i = 0; i < phase2; i++) {
        system.destroyComponent(phase2Handles[i]);
    }

    const size_t phase3 = 54;
    GlobalHandle phase3Handles[phase3];
    for (size_t i = 0; i < phase3; i++) {
        phase3Handles[i] = system.createComponent();
    }
}



















//#include <Engine->hpp>
//#include <Constants->hpp>
//#include <file/FileManager->hpp>
//#include <SDL_log->h>
//
//#define STB_IMAGE_IMPLEMENTATION
//#include <stb_image->h>
//
//#include <string>
//
//int main()
//{
//	SDL_LogSetAllPriority(SDL_LOG_PRIORITY_VERBOSE);
//
//    FileManager::initialize();
//
//	//std::string fullPath = FileManager::instance()->fullPathForFile("ImageTest->png");
//	//std::vector<char> data = FileManager::instance()->loadFile("ImageTest->png");
//
//    //int x, y, channels_in_file;
//    //stbi_uc* result = stbi_load(fullPath->c_str(), &x, &y, &channels_in_file, 4);
//    //stbi_image_free(result);
//
//
//    Engine* engine = new Engine();
//    if(engine->initialize()) {
//        engine->run();
//    }
//
//    return 0;
//}