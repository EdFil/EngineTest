//
// Created by edgar on 3/8/19.
//

#include "TransformSystem.h"

#include <iostream>
#include <cassert>

TransformComponent TransformSystem::s_invalidTransformComponent = {};

void TransformSystem::initWithCapacity(TransformComponentHandle capacity) {
    if (capacity <= 0) {
        std::cout << "[TransformSystem::initWithCapacity] Error: Capacity can not be <= 0" << std::endl;
    }
    _nextComponentHandle = 0;
    _components.resize(capacity);

    for (size_t i = 0; i < _components.size(); i++) {
        _components[i].nextComponentHandle = i + 1;
        _components[i].status =  ComponentStatus::Free;
    }
}

TransformComponentHandle TransformSystem::createComponent() {
    if (_nextComponentHandle >= static_cast<TransformComponentHandle>(_components.size())) {
        std::cout << "[TransformSystem::createComponent] Error: Component vector full. Resize not implemented yet" << std::endl;
        return k_invalidComponentHandle;
    }

    if (_nextComponentHandle < 0) {
        std::cout << "[TransformSystem::createComponent] Error: No more space for components" << std::endl;
        return k_invalidComponentHandle;
    }

    assert(_components[_nextComponentHandle].status == ComponentStatus::Free);

    TransformComponentHandle handleToReturn = _nextComponentHandle;
    _nextComponentHandle = _components[handleToReturn].nextComponentHandle;
    _components[handleToReturn].status = ComponentStatus::Used;

    std::cout << "Create component on Handle " << handleToReturn << " next is " << _nextComponentHandle << std::endl;

    return handleToReturn;
}

void TransformSystem::destroyComponent(const TransformComponentHandle componentHandle) {
    if (_nextComponentHandle > static_cast<TransformComponentHandle>(_components.size()) || _nextComponentHandle < 0) {
        std::cout << "[TransformSystem::destroyComponent] Error: Invalid component handle" << std::endl;
        return;
    }

    if (_components[componentHandle].status == ComponentStatus::Free) {
        std::cout << "[TransformSystem::destroyComponent] Warning: Component was already Free" << std::endl;
        return;
    }


    _components[componentHandle].status = ComponentStatus::Free;
    _components[componentHandle].nextComponentHandle = _nextComponentHandle;
    _nextComponentHandle = componentHandle;

    std::cout << "Delete component on Handle " << componentHandle << " next is " << _nextComponentHandle << std::endl;
}

TransformComponent& TransformSystem::getComponent(const TransformComponentHandle componentHandle) {
    if (_nextComponentHandle > static_cast<TransformComponentHandle>(_components.size()) || _nextComponentHandle < 0) {
        std::cout << "[TransformSystem::getComponent] Error: Invalid handle" << std::endl;
        return s_invalidTransformComponent;
    }

    return _components[componentHandle].component;
}
