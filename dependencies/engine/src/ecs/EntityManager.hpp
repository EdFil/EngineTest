#pragma once

#include "container/PODArray.hpp"

// Memory layout
//
// | EntityID[0], EntityID[1]         ... EntityID[N]     |
// | GenerationID[0], GenerationID[1] ... GenerationID[N] |

struct EntityID;
namespace entity_manager {
    extern const uint8_t kEntityIndexBits;
    extern const uint8_t kEntityGenerationBits;
    extern const uint32_t kEntityIndexMask;
    extern const uint32_t kEntityGenerationMask;
    extern const uint32_t kEntityGenerationMaxValue;
    
    extern const EntityID k_invalidEntity;
}

struct EntityID {
    uint32_t m_id;

    uint32_t index() const { return m_id & entity_manager::kEntityIndexMask; }
    uint8_t generation() const { return static_cast<uint8_t >((m_id & entity_manager::kEntityGenerationMask) >> entity_manager::kEntityIndexBits); }
    operator uint32_t() const { return m_id; }
};
using GenerationId = uint8_t;

struct Entity {
    Uint32 m_id;
    Uint8 m_generation;
};

class EntityManager {
public:
    EntityManager();
    ~EntityManager();
    EntityManager(const EntityManager& rhs) = delete;
    EntityManager(const EntityManager&& rhs) = delete;
    EntityManager& operator=(const EntityManager& rhs) = delete;
    EntityManager& operator=(const EntityManager&& rhs) = delete;

    bool initWithCapacity(uint32_t capacity);
    bool resize(uint32_t capacity);
    EntityID createEntity();
    void destroyEntity(EntityID handle);
    bool isValid(const EntityID& entity) const;

private:
	void* m_pData;
    EntityID* m_pEntities;
    GenerationId* m_pGeneration;
    uint32_t m_capacity;
    uint32_t m_nextAvailableEntityIndex;
};
