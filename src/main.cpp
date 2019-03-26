#include "ecs/TransformSystem.h"

int main() {
    TransformSystem* system = new TransformSystem();

    std::cout << "[main.cpp] Initialize System with 5 components" << std::endl;
    system->initWith(5);
    std::cout << std::endl;

    std::cout << "[main.cpp] Update()" << std::endl;
    system->update(0.0f);
    std::cout << std::endl;

    std::cout << "[main.cpp] Create 3 components" << std::endl;
    Handle handle0 = system->createComponent();
    Handle handle1 = system->createComponent();
    Handle handle2 = system->createComponent();
    Handle handle3 = system->createComponent();
    Handle handle4 = system->createComponent();

    system->checkSystem();
    std::cout << std::endl;

    std::cout << "[main.cpp] Update()" << std::endl;
    system->update(0.0f);
    system->checkSystem();
    std::cout << std::endl;

    std::cout << "[main.cpp] Delete middle component" << std::endl;
    system->releaseComponent(handle1);
    system->releaseComponent(handle2);
    system->releaseComponent(handle3);
    system->checkSystem();
    std::cout << std::endl;

    std::cout << "[main.cpp] Update()" << std::endl;
    system->update(0.0f);
    system->checkSystem();
    std::cout << std::endl;

    std::cout << "[main.cpp] Reorder()" << std::endl;
    system->reorder();
    system->checkSystem();
    std::cout << std::endl;

    std::cout << "[main.cpp] Update()" << std::endl;
    system->update(0.0f);
    system->checkSystem();
    std::cout << std::endl;

    std::cout << "[main.cpp] Create 1 component()" << std::endl;
    handle1 = system->createComponent();
    system->checkSystem();
    std::cout << std::endl;

    std::cout << "[main.cpp] Update()" << std::endl;
    system->update(0.0f);
    system->checkSystem();
    std::cout << std::endl;

    (void)handle0;
    (void)handle1;
    (void)handle2;

    std::cout << "[main.cpp] Delete System" << std::endl;
    delete system;

    return 0;
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