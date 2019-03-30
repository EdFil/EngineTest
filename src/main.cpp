#include <chrono>
#include "ecs/TransformSystem.h"


#define BENCHMARK(__PARAM__) \
{\
    auto start = std::chrono::high_resolution_clock::now();\
    __PARAM__\
    auto elapsed =  std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now() - start);\
    std::cout << "[TIME] Took "<< elapsed.count() << " stuffs" << std::endl;\
}

void test1() {
    auto system = new TransformSystem();

    std::cout << "[test1()] Initialize System with 3 components" << std::endl;
    system->initWith(3);
    std::cout << std::endl;

    std::cout << "[test1()] Update()" << std::endl;
    system->update(0.0f);
    std::cout << std::endl;

    std::cout << "[test1()] Create 3 components" << std::endl;
    Handle handle0 = system->createComponent();
    Handle handle1 = system->createComponent();
    Handle handle2 = system->createComponent();

    system->checkSystem();
    std::cout << std::endl;

    std::cout << "[test1()] Update()" << std::endl;
    system->update(0.0f);
    system->checkSystem();
    std::cout << std::endl;

    std::cout << "[test1()] Delete middle component" << std::endl;
    system->releaseComponent(handle1);
    system->checkSystem();
    std::cout << std::endl;

    std::cout << "[test1()] Update()" << std::endl;
    system->update(0.0f);
    system->checkSystem();
    std::cout << std::endl;

    std::cout << "[test1()] Reorder()" << std::endl;
    system->reorder();
    system->checkSystem();
    std::cout << std::endl;

    std::cout << "[test1()] Update()" << std::endl;
    system->update(0.0f);
    system->checkSystem();
    std::cout << std::endl;

    std::cout << "[test1()] Create 1 component()" << std::endl;
    handle1 = system->createComponent();
    system->checkSystem();
    std::cout << std::endl;

    std::cout << "[test1()] Update()" << std::endl;
    system->update(0.0f);
    system->checkSystem();
    std::cout << std::endl;

    std::cout << "[test1()] Remove last and first" << std::endl;
    system->releaseComponent(handle1);
    system->releaseComponent(handle0);
    system->checkSystem();
    std::cout << std::endl;

    std::cout << "[test1()] Update()" << std::endl;
    system->update(0.0f);
    system->checkSystem();
    std::cout << std::endl;

    std::cout << "[test1()] Reorder()" << std::endl;
    system->reorder();
    system->checkSystem();
    std::cout << std::endl;

    std::cout << "[test1()] Update()" << std::endl;
    system->update(0.0f);
    system->checkSystem();
    std::cout << std::endl;

    (void)handle0;
    (void)handle1;
    (void)handle2;

    std::cout << "[test1()] Delete System" << std::endl;
    delete system;
}

void test2() {
    TransformSystem* system = new TransformSystem();

    const size_t numComponents = 1000000;
    Handle createdHandles[numComponents];

    std::cout << "[test2()] Initialize System with "<< numComponents << " components" << std::endl;
    BENCHMARK(system->initWith(numComponents);)

    std::cout << "\n" << "[test2()] Create "<< numComponents << " components" << std::endl;
    BENCHMARK(for(size_t i = 0; i < numComponents; i++) {createdHandles[i] = system->createComponent();})

    std::cout << "\n" << "[test2()] Delete half even index components" << std::endl;
    BENCHMARK(for(size_t i = 0; i < numComponents; i+=2) {system->releaseComponent(createdHandles[i]);})

    std::cout << "\n" << "[test2()] Reorder" << std::endl;
    BENCHMARK(system->reorder();)

    TransformComponent* component = system->getComponent(createdHandles[1]);
    component->set(100, 100 ,100);

    std::cout << "End"<< std::endl;
    delete system;
}

int main() {
    test2();
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