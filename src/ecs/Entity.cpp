//
// Created by edgar on 5/18/19.
//

#include <algorithm>

#include "Entity.h"

void Entity::addComponenthandle(GlobalHandle globalHandle) {
    _componentHandles.push_back(globalHandle);
}

void Entity::removeComponentHandle(GlobalHandle globalHandle) {
    for (size_t i = 0; i < _componentHandles.size(); i++) {
        if (_componentHandles[i] == globalHandle) {
            _componentHandles[i] = _componentHandles.back();
            _componentHandles.pop_back();
            return;
        }
    }
}
