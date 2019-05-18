//
// Created by edgar on 3/8/19.
//

#include "TransformSystem.h"

#include <iostream>
#include <cassert>

void TransformSystem::initWithCapacity(int16_t capacity) {
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

GlobalHandle TransformSystem::createComponent() {
    if (_nextComponentHandle >= static_cast<LocalHandle>(_components.size())) {
        std::cout << "[TransformSystem::createComponent] Error: Component vector full. Resize not implemented yet" << std::endl;
        return -1;
    }

    if (_nextComponentHandle < 0) {
        std::cout << "[TransformSystem::createComponent] Error: No more space for components" << std::endl;
        return -1;
    }

    assert(_components[_nextComponentHandle].status == ComponentStatus::Free);

    LocalHandle localHandleToReturn = _nextComponentHandle;
    _nextComponentHandle = _components[localHandleToReturn].nextComponentHandle;
    _components[localHandleToReturn].status = ComponentStatus::Used;

    std::cout << "Create component on Handle " << localHandleToReturn << " next is " << _nextComponentHandle << std::endl;

    return transform_system_globals::k_transformHandlePrefix | localHandleToReturn;
}

void TransformSystem::destroyComponent(const GlobalHandle globalHandle) {
    if (_nextComponentHandle > static_cast<LocalHandle>(_components.size()) || _nextComponentHandle < 0) {
        std::cout << "[TransformSystem::destroyComponent] Error: Invalid component handle" << std::endl;
        return;
    }

    const LocalHandle localHandle = static_cast<LocalHandle>(globalHandle);
    if (_components[localHandle].status == ComponentStatus::Free) {
        std::cout << "[TransformSystem::destroyComponent] Warning: Component was already Free" << std::endl;
        return;
    }

    _components[localHandle].status = ComponentStatus::Free;
    _components[localHandle].nextComponentHandle = _nextComponentHandle;
    _nextComponentHandle = static_cast<LocalHandle>(localHandle);

    std::cout << "Delete component on Handle " << localHandle << " next is " << _nextComponentHandle << std::endl;
}

TransformComponent& TransformSystem::getComponent(const GlobalHandle globalHandle) {
    if (globalHandle > static_cast<LocalHandle >(_components.size()) || globalHandle < 0) {
        std::cout << "[TransformSystem::getComponent] Error: Invalid handle" << std::endl;
        return transform_system_globals::g_invalidTransformComponent;
    }

    return _components[static_cast<LocalHandle>(globalHandle)].component;
}
