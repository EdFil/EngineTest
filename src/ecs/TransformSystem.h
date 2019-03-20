#pragma once

#include <cstdint>
#include <iostream>
#include <algorithm>

#include "System.h"

#define DEBUG_TRANSFORMS
#ifdef DEBUG_TRANSFORMS
    #define DP_TRANSFORM(__PARAMS__) __PARAMS__
#else
    #define DP_TRANSFORM(__PARAMS__) do {} while(0);
#endif

struct TransformComponent {
    TransformComponent() : x(0.0f), y(0.0f), z(0.0f) { DP_TRANSFORM(std::cout << "[TransformComponent::Constructor]" << std::endl;) }
    TransformComponent(float x, float y, float z) : x(x), y(y), z(z)  { DP_TRANSFORM(std::cout << "[TransformComponent::ConstructorXYZ]" << std::endl;) }
    TransformComponent(const TransformComponent& rhs) : x(rhs.x), y(rhs.y), z(rhs.z) { DP_TRANSFORM(std::cout << "[TransformComponent::CopyConstructor]" << std::endl;) }
    TransformComponent(const TransformComponent&& rhs) noexcept : x(rhs.x), y(rhs.y), z(rhs.z) { DP_TRANSFORM(std::cout << "[TransformComponent::MoveConstructor]" << std::endl;) }
    TransformComponent& operator=(const TransformComponent& rhs) { DP_TRANSFORM(std::cout << "[TransformComponent::CopyAssignmentOperator]" << std::endl;) x = rhs.x; y = rhs.y;  z = rhs.z; return *this; }
    TransformComponent& operator=(const TransformComponent&& rhs) noexcept { DP_TRANSFORM(std::cout << "[TransformComponent::MoveAssignmentOperator]" << std::endl;) x = rhs.x; y = rhs.y;  z = rhs.z; return *this; }
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
            _components[i].component.set(i, i, i);
        }
    }

    void update(float) final {
        for (ComponentWrapper& componentWrapper : _components) {
            if (componentWrapper.state == ComponentWrapper::State::Unused) {
                break;
            } else if (componentWrapper.state == ComponentWrapper::State::Invalidated) {
                std::cout << "Skip" << std::endl;
                continue;
            }

            std::cout << "Transform [" << componentWrapper.component.x << ", " << componentWrapper.component.y << ", "
            << componentWrapper.component.z << "]" << std::endl;
        }
    }

    void reorder() final {
//        if (!_needsReorder) {
//            std::cout << "[TransformSystem::reorder] No reorder needed" << std::endl;
//            return;
//        }

        size_t lastUsedComponent = 0;
        for (size_t i = 0; i < _components.size(); i++) {
            ComponentWrapper& componentWrapper = _components[i];
            if (componentWrapper.state == ComponentWrapper::State::Used) {
                continue;
            } else if (componentWrapper.state == ComponentWrapper::State::Invalidated) {
                if (lastUsedComponent < i) {
                    for (lastUsedComponent = i + 1; lastUsedComponent < _components.size(); lastUsedComponent++) {
                        if (_components[lastUsedComponent].state != ComponentWrapper::State::Used) {
                            lastUsedComponent = lastUsedComponent - 1;
                            break;
                        }
                    }

                    if (lastUsedComponent > i) {
                        _components[i].component = _components[lastUsedComponent].component;
                        _components[i].state = ComponentWrapper::State::Used;
                        _components[lastUsedComponent].state = ComponentWrapper::State::Unused;
                    } else {
                        _components[i].state = ComponentWrapper::State::Unused;
                    }
                }

            } else {
                break;
            }
        }

        _needsReorder = false;
    }

};
