#include <Engine.hpp>
#include <Constants.hpp>
#include <file/FileManager.hpp>
#include <SDL_log.h>
#include <scene/Scene.hpp>
#include <TextureManager.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <string>

class MyScene : public Scene {
	Node* _node = nullptr;

	void onCreated() override {	
		SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "My onCreate()");

		SDL_Texture* texture = _engine->textureManager()->loadTexture("AnotherImage.png");
		
		_node = new Node();

		const GlobalHandle transformComponentHandle = _engine->transformSystem().create({ 100.0f, 100.0f, 0.0f });
		_node->addComponentHandle(transformComponentHandle);

		const GlobalHandle spriteComponentHandle = _engine->spriteSystem().createComponent(transformComponentHandle, texture);
		_node->addComponentHandle(spriteComponentHandle);
		
	}

	void onDestroy() override {
		delete _node;

		SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "My onDestroy()");
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