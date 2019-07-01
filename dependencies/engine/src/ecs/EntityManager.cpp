#include "EntityManager.hpp"

#include <SDL_log.h>
#include <SDL_assert.h>

// Helper functions

uint32_t isAliveValueToMask(bool isAlive) { return isAlive ? ENTITY_IS_ALIVE_MASK : 0; }
uint32_t generationValueToMask(uint8_t generation) { return generation << ENTITY_INDEX_BITS; }

uint32_t make_id(bool isAlive, uint8_t generation, uint32_t index) {
    return isAliveValueToMask(isAlive) | generationValueToMask(generation) | index;
}

EntityManager::EntityManager() : m_pData(nullptr), m_pEntities(nullptr), m_pGeneration(nullptr), m_capacity(0), m_nextAvailableEntityIndex(0) {
    static_assert(ENTITY_IS_ALIVE_BITS + ENTITY_GENERATION_BITS + ENTITY_INDEX_BITS == 32);
    static_assert(ENTITY_IS_ALIVE_MASK + ENTITY_GENERATION_MASK + ENTITY_INDEX_MASK == UINT32_MAX);
}

EntityManager::~EntityManager() {
    resize(0);
}

bool EntityManager::initWithCapacity(uint32_t capacity) {
    return resize(capacity);
}

bool EntityManager::resize(uint32_t capacity) {
    if (capacity > k_localIndex) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[EntityManager::resize]  Trying to create %d out of a max of %d. Clamping...", capacity, ENTITY_INDEX_MASK);
        capacity = ENTITY_INDEX_MASK;
    }

    if (capacity == m_capacity) {
        SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "[EntityManager::resize] Resize to %d but was already at that capacity. Skipping resize...", capacity);
        return false;
    }

    if (capacity == 0) {
        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "[EntityManager::resize] Resize to 0. Deleting memory...");
        SDL_free(m_pData);
		m_pData = nullptr;
        m_pEntities = nullptr;
        m_pGeneration = nullptr;
        m_capacity = 0;
        return true;
    }

    // Creation and copy of data
	const unsigned sizeOfEntities = sizeof(EntityID) * capacity;
	const unsigned sizeOfGenerationIds = sizeof(GenerationId) * capacity;
	const unsigned sizeOfNewData = sizeOfEntities + sizeOfGenerationIds;
    void* newData = SDL_realloc(m_pData, sizeOfNewData);
    if (newData != nullptr) {
		EntityID* newEntityData = static_cast<EntityID*>(newData);
		GenerationId* newGenerationData = reinterpret_cast<GenerationId*>(newEntityData + capacity);

		// Initialize newly allocated values
        if (capacity > m_capacity) {
            for (uint32_t i = m_capacity; i < capacity; i++) {
                *reinterpret_cast<uint32_t*>(static_cast<EntityID*>(newEntityData) + i) = i + 1;
                newGenerationData[i] = 0;
            }
        }

        m_pEntities = newEntityData;
        m_pGeneration = newGenerationData;
        m_capacity = capacity;
        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "[EntityManager::resize]  (Re)Allocated memory for %d entities. [%d]", capacity, sizeOfNewData);
        return true;
    } else {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[EntityManager::resize]  Error (re)allocating memory...");
    }

    return false;
}

EntityID EntityManager::createEntity() {
    SDL_assert(m_pEntities != nullptr);

    if (m_nextAvailableEntityIndex >= m_capacity) {
        SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "[EntityManager::createEntity] No more entities available, resizing...");
        if (!resize(m_capacity * 2)) {
            return k_invalidEntity;
        }
    }

    EntityID* entityToReturn = m_pEntities + m_nextAvailableEntityIndex;
    GenerationId* generation = m_pGeneration + m_nextAvailableEntityIndex;

    uint32_t newAvailableIndex = *reinterpret_cast<uint32_t*>(entityToReturn);
    entityToReturn->m_id = make_id(true, *generation, m_nextAvailableEntityIndex);
    m_nextAvailableEntityIndex = newAvailableIndex;

    return *entityToReturn;
}

void EntityManager::destroyEntity(const EntityID entity) {
    if (!isValid(entity)) { return; }

    uint32_t index = entity.index();
    m_pGeneration[index]++;
    if (m_pGeneration[index] >= ENTITY_GENERATION_MAX_VALUE) {
        m_pGeneration[index] = 0;
    }

    *reinterpret_cast<uint32_t*>(m_pEntities + index) = m_nextAvailableEntityIndex;
    m_nextAvailableEntityIndex = index;
}

bool EntityManager::isValid(const EntityID& entity) const {
    if (entity.isAlive()) {
        const uint32_t index = entity.index();
        return index <= m_capacity && entity.generation() == m_pGeneration[index];
    }

    return false;
}

