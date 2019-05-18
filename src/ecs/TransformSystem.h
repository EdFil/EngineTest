#pragma once

#include <cstdint>
#include <iostream>
#include <algorithm>

#include "System.h"

//#define DEBUG_TRANSFORMS
#ifdef DEBUG_TRANSFORMS
    #define DP_TRANSFORM(__PARAMS__) __PARAMS__
#else
    #define DP_TRANSFORM(__PARAMS__) do {} while(0);
#endif

struct TransformComponent {
    TransformComponent() : x(0.0f), y(0.0f), z(0.0f) { DP_TRANSFORM(std::cout << "[TransformComponent::Constructor]" << std::endl;) }
    TransformComponent(float x, float y, float z) : x(x), y(y), z(z)  { DP_TRANSFORM(std::cout << "[TransformComponent::ConstructorXYZ]" << std::endl;) }
    TransformComponent(const TransformComponent& rhs) : x(rhs.x), y(rhs.y), z(rhs.z) { DP_TRANSFORM(std::cout << "[TransformComponent::CopyConstructor]" << std::endl;) }
    TransformComponent(TransformComponent&& rhs) noexcept : x(rhs.x), y(rhs.y), z(rhs.z) { DP_TRANSFORM(std::cout << "[TransformComponent::MoveConstructor]" << std::endl;) }
    TransformComponent& operator=(const TransformComponent& rhs) { DP_TRANSFORM(std::cout << "[TransformComponent::CopyAssignmentOperator]" << std::endl;) x = rhs.x; y = rhs.y;  z = rhs.z; return *this; }
    TransformComponent& operator=(TransformComponent&& rhs) noexcept { DP_TRANSFORM(std::cout << "[TransformComponent::MoveAssignmentOperator]" << std::endl;) x = rhs.x; y = rhs.y;  z = rhs.z; return *this; }
    ~TransformComponent() { DP_TRANSFORM(std::cout << "[TransformComponent::Destructor]" << std::endl;) }

    void set(float _x, float _y, float _z) { x = _x; y = _y; z = _z; }

    float x, y, z;
};

using TransformComponentHandle = int16_t;
const TransformComponentHandle k_invalidComponentHandle = -1;

enum class ComponentStatus : int8_t {
    Free = 0, Used = 1
};

struct TransformWrapper {
    TransformComponent component;
    TransformComponentHandle nextComponentHandle;
    ComponentStatus status;
};

class TransformSystem {
public:
    static TransformComponent s_invalidTransformComponent;
    TransformComponentHandle _nextComponentHandle;
    std::vector<TransformWrapper> _components;


    TransformSystem() = default;
    ~TransformSystem() = default;

    void initWithCapacity(const TransformComponentHandle capacity);
    TransformComponentHandle createComponent();
    void destroyComponent(const TransformComponentHandle componentHandle);
    TransformComponent& getComponent(const TransformComponentHandle componentHandle);

private:
    TransformSystem(const TransformSystem&& rhs) = delete;
    TransformSystem( TransformSystem&& rhs) = delete;
    TransformSystem& operator=(const TransformSystem& rhs) = delete;
    TransformSystem& operator=(const TransformSystem&& rhs) = delete;
};
