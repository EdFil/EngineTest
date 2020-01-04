#include "EntityManager.hpp"

#include <SDL_assert.h>
#include <SDL_log.h>

bool EntityManager::initWithCapacity(Uint32 capacity) {
    return resize(capacity);
}

bool EntityManager::resize(Uint32 capacity) {
    if (capacity == 0) {
        capacity = 1;
    }

    return m_entityData.resize(capacity);
}

Entity EntityManager::createEntity() {
    if (m_nextIndex >= m_entityData.capacity()) {
        resize(m_nextIndex * 2);
    }

    EntityData& entityData = m_entityData[m_nextIndex];
    Entity entityToReturn{m_nextIndex, entityData.m_generation};

    if (entityData.m_nextIndex == 0) {
        m_nextIndex++;
    } else {
        m_nextIndex = entityData.m_nextIndex;
        entityData.m_nextIndex = 0;
    }

    return entityToReturn;
}

void EntityManager::destroyEntity(const Entity& entity) {
    if (!isValid(entity)) {
        return;
    }

    EntityData& entityData = m_entityData[entity.m_id];
    entityData.m_generation++;
    entityData.m_nextIndex = m_nextIndex;
    m_nextIndex = entity.m_id;
}

bool EntityManager::isValid(const Entity& entity) const {
    return entity.m_id < m_entityData.size() &&
           entity.m_generation == m_entityData[entity.m_id].m_generation;
}
