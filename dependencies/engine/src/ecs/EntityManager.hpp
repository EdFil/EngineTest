#pragma once

#include "container/Array.hpp"

struct Entity {
	Uint32 m_id;
    Uint32 m_generation;
};

class EntityManager {
public:
    EntityManager() = default;
    EntityManager(const EntityManager& rhs) = delete;
    EntityManager(const EntityManager&& rhs) = delete;
    EntityManager& operator=(const EntityManager& rhs) = delete;
    EntityManager& operator=(const EntityManager&& rhs) = delete;

    bool initWithCapacity(Uint32 capacity);
    bool resize(Uint32 capacity);
    Entity createEntity();
    void destroyEntity(const Entity& handle);
    bool isValid(const Entity& entity) const;

private:
    struct EntityData {
        Uint32 m_nextIndex;
        Uint32 m_generation;
    };

    Array<EntityData> m_entityData;
    Uint32 m_nextIndex = 0;
};
