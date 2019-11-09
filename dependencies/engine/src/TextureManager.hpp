#pragma once

#include <string>
#include <unordered_map>

struct SDL_Renderer;
struct SDL_Texture;

class TextureManager {
public:
    SDL_Texture* loadTexture(const std::string& textureFileName);

    void setRenderer(SDL_Renderer* renderer) { _renderer = renderer; };

private:
    SDL_Renderer* _renderer;
    std::unordered_map<std::string, SDL_Texture*> _cachedTextures;
};
