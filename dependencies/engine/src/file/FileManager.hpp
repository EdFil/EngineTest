#pragma once

#include <string>
#include <vector>

class FileManager {
public:
    static void initialize();
    static FileManager* instance();

	FileManager();

	std::vector<char> loadFile(const char fileName[]) const;

	/** Returns a full path for a given filename if it exists. Returns empty string if file not found. */
    std::string fullPathForFile(const char fileName[]) const;

    bool setRootDir(const char rootDir[]);

private:
	/** Resources root directory */
    std::string _rootDir;
};

