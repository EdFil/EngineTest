#include "FileManager.hpp"

#include <fstream>

#define RESOURCES_FOLDER "resources"

#ifdef _WIN32
#define FOLDER_SEP "\\"
#else
#define FOLDER_SEP "/"
#endif  // _WIN32

static FileManager* s_fileManager = nullptr;

void FileManager::initialize() {
    // SDL_assert(s_fileManager == nullptr); // FileManager is already initialized!!
    s_fileManager = new FileManager();
}

FileManager* FileManager::instance() {
    // SDL_assert(s_fileManager != nullptr);
    return s_fileManager;
}

FileManager::FileManager() {
    // char* basePath = SDL_GetBasePath();
    // if (basePath != nullptr) {
    // 	_rootDir.assign(basePath);
    // 	SDL_free(basePath);
    // }
}

std::vector<char> FileManager::loadFile(const char fileName[]) const {
    std::vector<char> fileDataVector;
    // std::string fullPath = fullPathForFile(fileName);

    // if (fullPath.empty()) {
    // 	return fileDataVector;
    // }

    // std::ifstream fileReader(fullPath.c_str(), std::ifstream::binary);
    // if (fileReader) {
    // 	// Get file size
    // 	fileReader.seekg(0, std::ifstream::end);
    // 	const std::streampos fileSize = fileReader.tellg();
    // 	fileReader.seekg(0, std::ifstream::beg);

    // 	fileDataVector.resize(fileSize);
    // 	fileReader.read(&fileDataVector[0], fileSize);

    // 	if (fileReader) {
    // 		SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "[FileManager] Read file %s",
    // fullPath.c_str()); 	} else { 		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[FileManager] Failed
    // to read file %s", fullPath.c_str());
    // 	}

    // 	fileReader.close();
    // } else {
    // 	SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[FileManager] Failed open file %s",
    // fullPath.c_str());
    // }

    return fileDataVector;
}

std::string FileManager::fullPathForFile(const char fileName[]) const {
    // Build file path
    return _rootDir + RESOURCES_FOLDER + FOLDER_SEP + fileName;
}

bool FileManager::setRootDir(const char* rootDir) {
    _rootDir = rootDir;
    return true;
}
