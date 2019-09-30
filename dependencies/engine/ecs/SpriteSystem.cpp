//
// Created by edgar on 3/8/19.
//

#include "SpriteSystem.hpp"

#include <cassert>

#include <SDL_log.h>
#include <SDL_render.h>
#include <iostream>

#include "Engine.hpp"
#include "ecs/TransformSystem.hpp"

void SpriteSystem::initWithCapacity(int16_t capacity) {
    if (capacity <= 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[SpriteSystem::initWithCapacity] Capacity can not be <= 0");
    }
    _nextComponentHandle = 0;
    _components.resize(capacity);

    for (size_t i = 0; i < _components.size(); i++) {
        _components[i].nextComponentHandle = i + 1;
        _components[i].status =  ComponentStatus::Free;
    }
}

GlobalHandle SpriteSystem::createComponent(GlobalHandle transformComponentHandle) {
	return createComponent(transformComponentHandle, nullptr);
}

GlobalHandle SpriteSystem::createComponent(GlobalHandle transformComponentHandle, SDL_Texture* texture) {
    if (_nextComponentHandle >= static_cast<LocalHandle>(_components.size())) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[SpriteSystem::createComponent] Component vector full. Resize not implemented yet");
        return -1;
    }

    assert(_components[_nextComponentHandle].status == ComponentStatus::Free);

	const LocalHandle localHandleToReturn = _nextComponentHandle;
    _nextComponentHandle = _components[localHandleToReturn].nextComponentHandle;
    _components[localHandleToReturn].status = ComponentStatus::Used;

	_components[localHandleToReturn].component.texture = texture;
	_components[localHandleToReturn].component.transformComponentHandle = transformComponentHandle;

	SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "[SpriteSystem::createComponent] Create component with Handle %d next is %d", localHandleToReturn , _nextComponentHandle);

    return sprite_system_globals::k_spriteHandlePrefix | localHandleToReturn;
}

void SpriteSystem::destroyComponent(const GlobalHandle globalHandle) {
    if (_nextComponentHandle > static_cast<LocalHandle>(_components.size())) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[SpriteSystem::destroyComponent] Invalid component handle %d", globalHandle);
        return;
    }

    const LocalHandle localHandle = static_cast<LocalHandle>(globalHandle);
    if (_components[localHandle].status == ComponentStatus::Free) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[SpriteSystem::destroyComponent] Component %d was already Free", globalHandle);
        return;
    }

    _components[localHandle].status = ComponentStatus::Free;
    _components[localHandle].nextComponentHandle = _nextComponentHandle;
    _nextComponentHandle = static_cast<LocalHandle>(localHandle);

	_components[localHandle].component.texture = nullptr;
	_components[localHandle].component.transformComponentHandle = -1;

    std::cout << "Delete component on Handle " << localHandle << " next is " << _nextComponentHandle << std::endl;
}

SpriteComponent& SpriteSystem::getComponent(const GlobalHandle globalHandle) {
	const LocalHandle localHandle = static_cast<LocalHandle>(globalHandle);
	
	if (localHandle > static_cast<LocalHandle >(_components.size())) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[SpriteSystem::getComponent] Invalid handle %d", globalHandle);
        return sprite_system_globals::g_invalidSpriteComponent;
    }

    return _components[localHandle].component;
}

void SpriteSystem::tempDraw(SDL_Renderer* renderer) {
	SDL_Rect destRect = {0, 0, 30, 30};
	TransformSystem& transformSystem = _engine.transformSystem();
	for (SpriteWrapper& spriteWrapper : _components) {
		if (spriteWrapper.status == ComponentStatus::Used) {
			TransformComponent& transformComponent = transformSystem.get(spriteWrapper.component.transformComponentHandle);
			
			destRect.x = transformComponent.position.x;
			destRect.y = transformComponent.position.y;

			SDL_RenderCopy(renderer, spriteWrapper.component.texture, nullptr, &destRect);
		}
	}
}
