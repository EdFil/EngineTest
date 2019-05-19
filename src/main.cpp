#include <Engine.hpp>
#include <Constants.hpp>
#include <file/FileManager.hpp>
#include <SDL_log.h>
#include <scene/Scene.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <string>

class MyScene : public Scene {
	void onCreated() override {	
		SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "My onCreate()");
	}

	void onDestroy() override {
		SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "My onDestroy()");
	}

	void update(float) override {	
		SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "My update()");
	}
};

int main()
{
	SDL_LogSetAllPriority(SDL_LOG_PRIORITY_VERBOSE);

    FileManager::initialize();

	//std::string fullPath = FileManager::instance()->fullPathForFile("ImageTest->png");
	//std::vector<char> data = FileManager::instance()->loadFile("ImageTest->png");

    //int x, y, channels_in_file;
    //stbi_uc* result = stbi_load(fullPath->c_str(), &x, &y, &channels_in_file, 4);
    //stbi_image_free(result);


    Engine* engine = new Engine();
    if(engine->initialize()) {
		engine->setScene(std::make_unique<MyScene>());
        engine->run();
    }

    return 0;
}