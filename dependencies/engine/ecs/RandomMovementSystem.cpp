//
// Created by edgar on 3/8/19.
//

#include "RandomMovementSystem.hpp"

#include <cassert>

#include <SDL_log.h>
#include <SDL_render.h>

#include "Engine.hpp"
#include "ecs/TransformSystem.hpp"
#include "ecs/SpriteSystem.hpp"

void RandomMovementSystem::initWithCapacity(int16_t capacity) {
    if (capacity <= 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[RandomMovementSystem::initWithCapacity] Capacity can not be <= 0");
    }
    _nextComponentHandle = 0;
    _components.resize(capacity);

    for (size_t i = 0; i < _components.size(); i++) {
        _components[i].nextComponentHandle = i + 1;
        _components[i].status =  ComponentStatus::Free;
    }

	SDL_Rect rect;
	SDL_RenderGetViewport(_engine.renderer(), &rect);
	_resolutionX = rect.w;
	_resolutionY = rect.h;
}

GlobalHandle RandomMovementSystem::createComponent(GlobalHandle transformComponentHandle, GlobalHandle spriteComponentHandle) {
    if (_nextComponentHandle >= static_cast<LocalHandle>(_components.size())) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[RandomMovementSystem::createComponent] Component vector full. Resize not implemented yet");
        return -1;
    }

    assert(_components[_nextComponentHandle].status == ComponentStatus::Free);

	const LocalHandle localHandleToReturn = _nextComponentHandle;
    _nextComponentHandle = _components[localHandleToReturn].nextComponentHandle;
    _components[localHandleToReturn].status = ComponentStatus::Used;

	_components[localHandleToReturn].component.transformComponentHandle = transformComponentHandle;
	_components[localHandleToReturn].component.spriteComponentHandle = spriteComponentHandle;
	_components[localHandleToReturn].component.direction = Vector3(rand() % 2 == 0 ? -1 : 1, rand() % 2 == 0 ? -1 : 1, 0.0f);
	TransformComponent& transformComponent = _engine.transformSystem().get(transformComponentHandle);
	transformComponent.position = Vector3(rand() % _resolutionX - 30, rand()	 % _resolutionY - 30, 0.0f);

	SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "[RandomMovementSystem::createComponent] Create component with Handle %d next is %d", localHandleToReturn , _nextComponentHandle);

    return sprite_system_globals::k_spriteHandlePrefix | localHandleToReturn;
}

void RandomMovementSystem::destroyComponent(const GlobalHandle globalHandle) {
    if (_nextComponentHandle > static_cast<LocalHandle>(_components.size())) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[RandomMovementSystem::destroyComponent] Invalid component handle %d", globalHandle);
        return;
    }

    const LocalHandle localHandle = static_cast<LocalHandle>(globalHandle);
    if (_components[localHandle].status == ComponentStatus::Free) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[RandomMovementSystem::destroyComponent] Component %d was already Free", globalHandle);
        return;
    }

    _components[localHandle].status = ComponentStatus::Free;
    _components[localHandle].nextComponentHandle = _nextComponentHandle;
    _nextComponentHandle = static_cast<LocalHandle>(localHandle);

	_components[localHandle].component.transformComponentHandle = -1;
	_components[localHandle].component.spriteComponentHandle = -1;

    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Delete component on Handle %d next is %d.", localHandle, _nextComponentHandle);
}

RandomMovementComponent& RandomMovementSystem::getComponent(const GlobalHandle globalHandle) {
    if (globalHandle > static_cast<LocalHandle >(_components.size())) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[RandomMovementSystem::getComponent] Invalid handle %d", globalHandle);
        return random_movement_system_globals::g_invalidRandomMovementComponent;
    }

    return _components[static_cast<LocalHandle>(globalHandle)].component;
}

void RandomMovementSystem::update(float delta) {
	static const float k_moveAmount = 200.0f;

	for (RandomMovementComponentWrapper& randomMovementComponentWrapper : _components) {
		if (randomMovementComponentWrapper.status == ComponentStatus::Used) {
			TransformComponent& transformComponent = _engine.transformSystem().get(randomMovementComponentWrapper.component.transformComponentHandle);
			RandomMovementComponent& randomMovementComponent = randomMovementComponentWrapper.component;

			transformComponent.position.x += randomMovementComponent.direction.x * k_moveAmount * delta;
			transformComponent.position.y += randomMovementComponent.direction.y * k_moveAmount * delta;

			if (transformComponent.position.x <= 0.0f || transformComponent.position.x + 30.0f> _resolutionX) {
				randomMovementComponent.direction.x *= -1;
			}

			if (transformComponent.position.y <= 0.0f || transformComponent.position.y + 30.0f> _resolutionY) {
				randomMovementComponent.direction.y *= -1;
			}
		}
	}
}
