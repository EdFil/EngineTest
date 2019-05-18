#pragma once

#include <iostream>
#include <vector>

#include "ECS.h"

struct TransformComponent {
    float x, y, z;
};

enum class ComponentStatus : int8_t {
    Free = 0, Used = 1
};

struct TransformWrapper {
    TransformComponent component;
    LocalHandle nextComponentHandle;
    ComponentStatus status;
};

namespace transform_system_globals {
    static const GlobalHandle k_transformHandlePrefix = 0x00010000;
    static TransformComponent g_invalidTransformComponent = TransformComponent();
}

class TransformSystem {
public:
    std::vector<TransformWrapper> _components;
    LocalHandle _nextComponentHandle;

    TransformSystem() = default;

    void initWithCapacity(int16_t capacity);
    GlobalHandle createComponent();
    void destroyComponent(GlobalHandle componentHandle);
    TransformComponent& getComponent(GlobalHandle componentHandle);

private:
    TransformSystem(const TransformSystem&& rhs) = delete;
    TransformSystem( TransformSystem&& rhs) = delete;
    TransformSystem& operator=(const TransformSystem& rhs) = delete;
    TransformSystem& operator=(const TransformSystem&& rhs) = delete;
};
