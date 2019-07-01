#pragma once

#include <vector>

#include "ECS.hpp"

struct SDL_Renderer;
struct SDL_Texture;

class Engine;

struct SpriteComponent {
	SDL_Texture* texture;
	GlobalHandle transformComponentHandle;
};

struct SpriteWrapper {
    SpriteComponent component;
    LocalHandle nextComponentHandle;
    ComponentStatus status;
};

namespace sprite_system_globals {
    static const GlobalHandle k_spriteHandlePrefix = 0x00020000;
    static SpriteComponent g_invalidSpriteComponent = SpriteComponent();
}

class SpriteSystem {
public:
    std::vector<SpriteWrapper> _components;
    LocalHandle _nextComponentHandle;

	SpriteSystem(Engine& engine) : _engine(engine) {}

    void initWithCapacity(int16_t capacity);
    GlobalHandle createComponent(GlobalHandle transformComponentHandle);
	GlobalHandle createComponent(GlobalHandle transformComponentHandle, SDL_Texture* texture);

    void destroyComponent(GlobalHandle componentHandle);
    SpriteComponent& getComponent(GlobalHandle componentHandle);

	void tempDraw(SDL_Renderer* renderer);

private:
	Engine& _engine;

	SpriteSystem(const SpriteSystem&& rhs) = delete;
	SpriteSystem(SpriteSystem&& rhs) = delete;
	SpriteSystem& operator=(const SpriteSystem& rhs) = delete;
	SpriteSystem& operator=(const SpriteSystem&& rhs) = delete;
};
