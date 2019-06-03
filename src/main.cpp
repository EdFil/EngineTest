#include <Engine.hpp>
#include <Constants.hpp>
#include <file/FileManager.hpp>
#include <SDL_log.h>
#include <TextureManager.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <string>
#include <ctime>

int main()
{
	srand(time(nullptr));

	SDL_LogSetAllPriority(SDL_LOG_PRIORITY_VERBOSE);

    FileManager::initialize();

	//std::string fullPath = FileManager::instance()->fullPathForFile("ImageTest->png");
	//std::vector<char> data = FileManager::instance()->loadFile("ImageTest->png");

    //int x, y, channels_in_file;
    //stbi_uc* result = stbi_load(fullPath->c_str(), &x, &y, &channels_in_file, 4);
    //stbi_image_free(result);


    Engine* engine = new Engine();
    if(engine->initialize()) {
        engine->run();
    }

    return 0;
}