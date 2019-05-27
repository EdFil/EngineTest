#pragma once

#include <cstdint>

using ObjectPoolHandle = uint32_t;
static const ObjectPoolHandle k_invalidHandle = UINT32_MAX;

#define MIN(__ARG1__, __ARG2__) (__ARG1__ < __ARG2__ ? __ARG1__ : __ARG2__)

template <typename T>
class ObjectPool {
    T* m_pObjects;
    uint32_t m_capacity;
    uint32_t m_nextHandle;

public:
    ObjectPool() : m_pObjects(nullptr), m_capacity(0), m_nextHandle(0) {}
    ~ObjectPool() {
        if (m_pObjects != nullptr)
            free(m_pObjects);
    }


    bool initWithSize(const uint32_t capacity) {
        if (!resize(capacity)) { return false; }

        reset();
        return true;
    }
    bool resize(const uint32_t capacity) {
        // Auxiliary variables
        bool result = false;
        T* pOldObjects = m_pObjects;
        uint32_t oldCapacity = m_capacity;

        // Creation and copy of data
        m_pObjects = (T*)malloc(sizeof(T) * capacity);
        if (m_pObjects != nullptr) {
            m_capacity = capacity;

            if (pOldObjects != nullptr) {
                memcpy(m_pObjects, pOldObjects, sizeof(T) * MIN(oldCapacity, m_capacity));
            }

            result = true;
        }

        // Cleanup
        if (pOldObjects != nullptr)
            free(pOldObjects);

        return result;
    }
    void reset() {
        assert(m_pObjects != nullptr);

        for (uint32_t i = 0; i < m_capacity; i++) {
            *reinterpret_cast<uint32_t*>(m_pObjects + i) = i + 1;
        }
    }

    ObjectPoolHandle getNewHandle() {
        if (m_nextHandle >= m_capacity || m_nextHandle == k_invalidHandle) {
            return k_invalidHandle;
        }

        const ObjectPoolHandle handleToReturn = m_nextHandle;
        m_nextHandle = *(uint32_t*)(m_pObjects + m_nextHandle);
        return handleToReturn;
    }
    void releaseHandle(const ObjectPoolHandle handle) {
        if (handle >= m_capacity || handle == k_invalidHandle) {
            return;
        }

        *(uint32_t*)(m_pObjects + handle) = m_nextHandle;
        m_nextHandle = handle;
    }

    T& operator[](const ObjectPoolHandle handle) {
        assert(m_nextHandle < m_capacity || m_nextHandle != k_invalidHandle);
        return m_pObjects[handle];
    }
};
