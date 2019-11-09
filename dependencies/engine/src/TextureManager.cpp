#include "TextureManager.hpp"

#include <SDL_log.h>
#include <SDL_render.h>
#include <stb_image.h>

#include "file/FileManager.hpp"

SDL_Texture* TextureManager::loadTexture(const std::string& textureFileName) {
    // If texture already cached
    const auto& it = _cachedTextures.find(textureFileName);
    if (it != _cachedTextures.cend()) {
        return it->second;
    }

    // Try to load the image into ram
    std::string imageFullPath = FileManager::instance()->fullPathForFile(textureFileName.c_str());
    int width, height, channelsInFile;

    stbi_uc* imageData =
        stbi_load(imageFullPath.c_str(), &width, &height, &channelsInFile, STBI_default);
    if (imageData == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_RENDER, "[TextureManager] Error loading image %s",
                     imageFullPath.c_str());
        return nullptr;
    }

    // Set up the pixel format color masks for RGB(A) byte arrays.
    // Only STBI_rgb (3) and STBI_rgb_alpha (4) are supported here!
    uint32_t rmask, gmask, bmask, amask;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    int shift = (req_format == STBI_rgb) ? 8 : 0;
    rmask = 0xff000000 >> shift;
    gmask = 0x00ff0000 >> shift;
    bmask = 0x0000ff00 >> shift;
    amask = 0x000000ff >> shift;
#else  // little endian, like x86
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = (channelsInFile == STBI_rgb) ? 0 : 0xff000000;
#endif

    // Setup channels
    int depth, pitch;
    if (channelsInFile == STBI_rgb) {
        depth = 24;
        pitch = 3 * width;  // 3 bytes per pixel * pixels per row
    } else {                // STBI_rgb_alpha (RGBA)
        depth = 32;
        pitch = 4 * width;
    }

    SDL_Surface* surface = SDL_CreateRGBSurfaceFrom(static_cast<void*>(imageData), width, height,
                                                    depth, pitch, rmask, gmask, bmask, amask);
    if (surface == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_RENDER, "Error creating surface for image %s with error %s",
                     imageFullPath.c_str(), SDL_GetError());
        stbi_image_free(imageData);
        return nullptr;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(_renderer, surface);
    SDL_FreeSurface(surface);
    stbi_image_free(imageData);
    if (texture == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_RENDER, "Error creating texture for image %s with error %s",
                     imageFullPath.c_str(), SDL_GetError());
    }

    return texture;
}
