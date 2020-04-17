#include "ecs/TransformSystem.hpp"

edgine::TransformSystem::TransformSystem() : m_nextHandle(0) {
}

edgine::TransformHandle edgine::TransformSystem::createComponent() {

    return TransformHandle();
}
