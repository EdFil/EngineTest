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
    TransformComponent(const TransformComponent&& rhs) : x(rhs.x), y(rhs.y), z(rhs.z) { DP_TRANSFORM(std::cout << "[TransformComponent::MoveConstructor]" << std::endl;) }
    TransformComponent& operator=(const TransformComponent& rhs) { DP_TRANSFORM(std::cout << "[TransformComponent::CopyAssignmentOperator]" << std::endl;) x = rhs.x; y = rhs.y;  z = rhs.z; return *this; }
    TransformComponent& operator=(const TransformComponent&& rhs) { DP_TRANSFORM(std::cout << "[TransformComponent::MoveAssignmentOperator]" << std::endl;) x = rhs.x; y = rhs.y;  z = rhs.z; return *this; }
    ~TransformComponent() { DP_TRANSFORM(std::cout << "[TransformComponent::Destructor]" << std::endl;) }

    void set(float _x, float _y, float _z) { x = _x; y = _y; z = _z; }

    float x, y, z;
};

class TransformSystem : public System<TransformComponent> {
public:

    ~TransformSystem() final = default;

    void initWith(size_t capacity) final {
        System::initWith(capacity);
        for (size_t i = 0; i < _components.size(); i++) {
            _components[i].component.set(static_cast<float>(i), static_cast<float>(i), static_cast<float>(i));
        }
    }

    void update(float) final {
        for (ComponentWrapper& componentWrapper : _components) {
            if (componentWrapper.state == ComponentWrapper::State::Unused) {
                std::cout << "Unused" << std::endl;
                continue;
            } else if (componentWrapper.state == ComponentWrapper::State::Invalidated) {
                std::cout << "Invalid" << std::endl;
                continue;
            }

            std::cout << "Transform [" << componentWrapper.component.x << ", " << componentWrapper.component.y << ", "
            << componentWrapper.component.z << "]" << std::endl;
        }
    }

    void reorder() final {
        if (!_needsReorder) {
            std::cout << "[TransformSystem::reorder] No reorder needed" << std::endl;
            return;
        }

        size_t firstInvalidatedComponentIndex = _components.size();
        for (size_t i = 0; i < _components.size(); i++) {
            ComponentWrapper& componentWrapper = _components[i];
            if (componentWrapper.state == ComponentWrapper::State::Used) {
                if (firstInvalidatedComponentIndex < i) {
                    _components[firstInvalidatedComponentIndex].component = _components[i].component;
                    _components[firstInvalidatedComponentIndex].state = ComponentWrapper::State::Used;
                    _components[firstInvalidatedComponentIndex].handle = _components[i].handle;
                    _handles[_components[firstInvalidatedComponentIndex].handle] = static_cast<Handle>(firstInvalidatedComponentIndex);

                    _components[i].handle = k_invalidHandle;
                    _components[i].state = ComponentWrapper::State::Invalidated;
                    firstInvalidatedComponentIndex++;
                }
            } else if (componentWrapper.state == ComponentWrapper::State::Invalidated) {
                if (firstInvalidatedComponentIndex > i) {
                    firstInvalidatedComponentIndex = i;
                }
            } else {
                break;
            }
        }

        if (firstInvalidatedComponentIndex != _components.size()) {
            _firstAvailableComponentIndex  = firstInvalidatedComponentIndex;
            for (; firstInvalidatedComponentIndex < _components.size(); firstInvalidatedComponentIndex++) {
                _components[firstInvalidatedComponentIndex].state = ComponentWrapper::State::Unused;
            }
        }

        _needsReorder = false;
    }

};
