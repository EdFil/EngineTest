#pragma once

#include <SDL_assert.h>
#include <SDL_log.h>
#include <SDL_stdinc.h>

#include <utility>

template <typename T>
class ObjectArray;

template <typename T>
class Array {
public:
    Array();
    explicit Array(Uint32 size);
    ~Array();

    /** Returns true is array is empty */
    bool isEmpty() const;

    /** Returns the number of elements in the array */
    Uint32 size() const;

    /** Returns the number of elements in the array */
    Uint32 capacity() const;

    /** Resize the array so it can fit 'size' elements */
    bool resize(Uint32 size);

    bool reserve(Uint32 size);

    /** Create a element on the back and return a reference to it */
    T& create_back();

    /** Copy this element to the back to the array */
    void push_back(const T& object);

    /** Gets array element on index 'index' */
    T& operator[](Uint32 index);

    /** Gets const array element on index 'index' */
    const T& operator[](Uint32 index) const;

    /** Gets a pointer to the beginning of the array */
    T* begin();

    /** Gets a const pointer to the beginning of the array */
    const T* begin() const;

    /** Gets a pointer to the end of the array */
    T* end();

    /** Gets a const pointer to the end of the array */
    const T* end() const;

    /** Gets a reference to the beginning of the array */
    T& front();

    /** Gets a const reference to the beginning of the array */
    const T& front() const;

    /** Gets a reference to the end of the array */
    T& back();

    /** Gets a const reference to the end of the array */
    const T& back() const;

private:
    Uint32 m_size;
    Uint32 m_capacity;
    T* m_pData;

    friend class ObjectArray<T>;

    bool alloc(Uint32 capacity);
};

// -----------------

template <typename T>
Array<T>::Array() : m_size(0), m_capacity(0), m_pData(nullptr) {
}

template <typename T>
Array<T>::Array(Uint32 size) : m_size(0), m_capacity(0), m_pData(nullptr) {
    reserve(size);
}

template <typename T>
Array<T>::~Array() {
    SDL_free(m_pData);
}

template <typename T>
bool Array<T>::isEmpty() const {
    return m_size == 0;
}

template <typename T>
Uint32 Array<T>::size() const {
    return m_size;
}

template <typename T>
Uint32 Array<T>::capacity() const {
    return m_capacity;
}

template <typename T>
bool Array<T>::reserve(Uint32 capacity) {
    if (m_capacity >= capacity) {
        return true;
    }

    return alloc(capacity);
}

template <typename T>
bool Array<T>::resize(Uint32 capacity) {
    Uint32 oldCapacity = m_capacity;
    if (!alloc(capacity)) {
        return false;
    }

    m_size = capacity;
    if (capacity > oldCapacity) {
        return SDL_memset(m_pData + oldCapacity, 0, sizeof(T) * (capacity - oldCapacity));
    }

    return true;
}

template <typename T>
T& Array<T>::create_back() {
    if (m_size == m_capacity) {
        if (!reserve(SDL_max(1, m_capacity * 2))) {
            SDL_assert(false);
        }
    }

    return m_pData[m_size++];
}

template <typename T>
void Array<T>::push_back(const T& object) {
    create_back() = object;
}

template <typename T>
T& Array<T>::operator[](Uint32 index) {
    SDL_assert(index < m_size);
    return m_pData[index];
}

template <typename T>
const T& Array<T>::operator[](Uint32 index) const {
    SDL_assert(index < m_size);
    return m_pData[index];
}

template <typename T>
T* Array<T>::begin() {
    return m_pData;
}

template <typename T>
const T* Array<T>::begin() const {
    return m_pData;
}

template <typename T>
T* Array<T>::end() {
    return m_pData + m_size;
}

template <typename T>
const T* Array<T>::end() const {
    return m_pData + m_size;
}

template <typename T>
T& Array<T>::front() {
    SDL_assert(m_size > 0);
    return m_pData[0];
}

template <typename T>
const T& Array<T>::front() const {
    SDL_assert(m_size > 0);
    return m_pData[0];
}

template <typename T>
T& Array<T>::back() {
    SDL_assert(m_size > 0);
    return m_pData[m_size - 1];
}

template <typename T>
const T& Array<T>::back() const {
    SDL_assert(m_size > 0);
    return m_pData[m_size - 1];
}

template <typename T>
bool Array<T>::alloc(Uint32 capacity) {
    if (capacity == 0 || m_capacity == capacity) return false;

    if (void* newData = SDL_malloc(sizeof(T) * capacity)) {
        T* castedNewData = static_cast<T*>(newData);
        if (m_size != 0) {
            SDL_memcpy(newData, m_pData, sizeof(T) * SDL_min(capacity, m_capacity));
            SDL_free(m_pData);
        }

        m_pData = castedNewData;
        m_capacity = capacity;
        m_size = SDL_min(m_size, capacity);
        return true;
    } else {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[Array::resize] Error allocating memory.");
        return false;
    }
}