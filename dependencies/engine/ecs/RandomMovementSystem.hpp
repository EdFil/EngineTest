#pragma once

#include <vector>

#include "ECS.hpp"
#include "math/Vector3f.hpp"

class Engine;

struct RandomMovementComponent {
	GlobalHandle transformComponentHandle;
	GlobalHandle spriteComponentHandle;
	Vector3 direction;
};

struct RandomMovementComponentWrapper {
    RandomMovementComponent component;
    LocalHandle nextComponentHandle;
    ComponentStatus status;
};

namespace random_movement_system_globals {
    static const GlobalHandle k_spriteHandlePrefix = 0x00030000;
    static RandomMovementComponent g_invalidRandomMovementComponent = RandomMovementComponent();
}

class RandomMovementSystem {
public:
    std::vector<RandomMovementComponentWrapper> _components;
    LocalHandle _nextComponentHandle;

	RandomMovementSystem(Engine& engine) : _engine(engine) {}

    void initWithCapacity(int16_t capacity);
    GlobalHandle createComponent(GlobalHandle transformComponentHandle, GlobalHandle spriteComponentHandle);

    void destroyComponent(GlobalHandle componentHandle);
    RandomMovementComponent& getComponent(GlobalHandle componentHandle);

	void update(float delta);

private:
	Engine& _engine;
	int _resolutionX, _resolutionY;

	RandomMovementSystem(const RandomMovementSystem&& rhs) = delete;
	RandomMovementSystem(RandomMovementSystem&& rhs) = delete;
	RandomMovementSystem& operator=(const RandomMovementSystem& rhs) = delete;
	RandomMovementSystem& operator=(const RandomMovementSystem&& rhs) = delete;
};
