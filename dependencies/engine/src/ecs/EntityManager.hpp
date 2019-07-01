#pragma once

#include "ECS.hpp"

// EntityID breakdown. 32 bit unsigned integer
//
//      0000 0000 0000 0000 0000 0000 0000 0000
//      ||____ _| |____________ ______________|
//      |     ^                ^
//      |  Generation      LocalIndex
//   Is Alive

#define ENTITY_INDEX_BITS 24u
#define ENTITY_INDEX_MASK 0x00FFFFFFu
#define ENTITY_IS_ALIVE_BITS 1u
#define ENTITY_IS_ALIVE_MASK 0x80000000u
#define ENTITY_GENERATION_BITS 7u
#define ENTITY_GENERATION_MASK 0x7F000000u
#define ENTITY_GENERATION_MAX_VALUE ENTITY_GENERATION_MASK >> ENTITY_INDEX_BITS

struct EntityID {
    uint32_t m_id;

    uint32_t index() const { return m_id & ENTITY_INDEX_MASK; }
    uint8_t generation() const { return static_cast<uint8_t >((m_id & ENTITY_GENERATION_MASK) >> ENTITY_INDEX_BITS); }
    uint32_t isAlive() const { return (m_id & ENTITY_IS_ALIVE_MASK) != 0; }
    operator uint32_t() const { return m_id; }
};

static const EntityID k_invalidEntity = EntityID{0xFFFF};

class EntityManager {
public:
    EntityManager();
    ~EntityManager();
    EntityManager(const EntityManager&& rhs) = delete;
    EntityManager(EntityManager&& rhs) = delete;
    EntityManager& operator=(const EntityManager& rhs) = delete;
    EntityManager& operator=(const EntityManager&& rhs) = delete;

    bool initWithCapacity(uint32_t capacity);
    bool resize(uint32_t capacity);
    EntityID createEntity();
    void destroyEntity(EntityID handle);
    bool isValid(const EntityID& entity) const;

private:
    EntityID* m_pEntities;
    uint8_t* m_pGeneration;
    uint32_t m_capacity;
    uint32_t m_nextIndex;
};
