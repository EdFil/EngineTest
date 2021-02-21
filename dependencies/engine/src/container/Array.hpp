#pragma once

#include <SDL_assert.h>
#include <SDL_stdinc.h>
#include <utility>

#include "logger/Logger.hpp"

template <typename T>
class ObjectArray {
public:
    ObjectArray() = default;

    ObjectArray(uint32_t capacity) { reserve(capacity); }

    ~ObjectArray() {
        if (m_pData) {
            for (uint32_t i = 0; i < m_size; ++i) {
                m_pData[i].~T();
            }
            SDL_free(m_pData);
        }
    }

    /** Returns true is array is empty */
    bool isEmpty() const { return m_size == 0; }

    /** Returns the number of elements in the array */
    uint32_t size() const { return m_size; }

    /** Returns how many elements this array can hold without having to re-allocate */
    uint32_t capacity() const { return m_capacity; }

    /** Resize the array so it can fit 'size' elements */
    bool resize(uint32_t capacity);

    /** Copy this element to the back to the array */
    void push_back(const T& object) {
        if (ensureCapacityForNewElement()) {
            m_pData[m_size++] = object;
        }
    }

    /** Move this element to the back to the array */
    void push_back(T&& object) noexcept {
        if (ensureCapacityForNewElement()) {
            m_pData[m_size++] = std::move(object);
        }
    }

    /** Create a new element at back to the array using the constructor */
    template <typename... Ts>
    T* emplace_back(Ts&&... args) {
        if (ensureCapacityForNewElement()) {
            return new (&m_pData[m_size++]) T(std::forward<Ts>(args)...);
        }

        return nullptr;
    }

    /** Remove all elements starting from the element provided. erase(std::remove()) idiom */
    void erase(T* value) {
        if (value > m_pData) {
            int index = value - m_pData;
            for (uint32_t i = index; i < m_size; ++i) {
                m_pData[i].~T();
            }
            m_size = index;
        }
    }

    /** Remove element at index */
    void removeAtIndex(uint32_t i) { erase(m_pData + i); }

    /** Gets array element on index 'index' */
    T& operator[](uint32_t index) { 
        SDL_assert(index >= 0 && index < m_size);
        return m_pData[index]; 
    }

    /** Gets const array element on index 'index' */
    const T& operator[](uint32_t index) const { 
        SDL_assert(index >= 0 && index < m_size);
        return m_pData[index]; 
    }

    /** Gets a pointer to the beginning of the array */
    T* begin() { return m_pData; }

    /** Gets a const pointer to the beginning of the array */
    const T* begin() const { return m_pData; }

    /** Gets a pointer to the end of the array. End is not the last element, it's 1 beyond that. */
    T* end() { return m_pData + m_size; }

    /** Gets a const pointer to the end of the array. End is not the last element, it's 1 beyond that. */
    const T* end() const { return m_pData + m_size; }

    /** Gets a reference to the beginning of the array */
    T& front() {
        SDL_assert(m_size > 0);
        return *m_pData;
    }

    /** Gets a const reference to the beginning of the array */
    const T& front() const {
        SDL_assert(m_size > 0);
        return *m_pData;
    }

    /** Gets a reference to the end of the array */
    T& back() {
        SDL_assert(m_size > 0);
        return m_pData[m_size - 1];
    }

    /** Gets a const reference to the end of the array */
    const T& back() const {
        SDL_assert(m_size > 0);
        return m_pData[m_size - 1];
    }

private:
    uint32_t m_size = 0;
    uint32_t m_capacity = 0;
    T* m_pData = nullptr;

    bool ensureCapacityForNewElement();
};

template <typename T>
bool ObjectArray<T>::resize(uint32_t capacity) {
    if (m_capacity == capacity) return true;

    if (capacity == 0) {
        for (uint32_t i = 0; i < m_size; ++i) {
            m_pData[i].~T();
        }

        SDL_free(m_pData);
        m_pData = nullptr;
        m_size = m_capacity = 0;
        return true;
    }

    if (void* newData = SDL_malloc(sizeof(T) * capacity)) {
        T* castedNewData = static_cast<T*>(newData);
        if (m_size != 0) {
            const uint32_t numObjectToMove = SDL_min(m_size, capacity);
            for (size_t i = 0; i < numObjectToMove; i++) {
                new (castedNewData + i) T(std::move(m_pData[i]));
            }

            if (capacity < m_size) {
                for (uint32_t i = numObjectToMove; i < m_size; i++) {
                    castedNewData[i].~T();
                }
            }
        }

        SDL_free(m_pData);
        m_pData = castedNewData;
        m_capacity = capacity;
        m_size = SDL_min(m_size, capacity);
        return true;
    } else {
        LOG_ERROR("[ObjectArray::resize] Error allocating memory.");
        return false;
    }
}

template <typename T>
inline bool ObjectArray<T>::ensureCapacityForNewElement() {
    if (m_size == m_capacity) {
        if (!resize(SDL_max(1, m_capacity * 2))) {
            SDL_assert(false);
            return false;
        }
    }

    return true;
}