#pragma once

#include "container/Array.hpp"

template <typename T>
class ObjectArray {
public:
    ObjectArray();
    explicit ObjectArray(Uint32 size);
    ~ObjectArray();

    /** Returns true is array is empty */
    bool isEmpty() const;

    /** Returns the number of elements in the array */
    Uint32 size() const;

    /** Resize the array so it can fit 'size' elements */
    bool resize(Uint32 size);

    /** Create a element on the back and return a reference to it */
    T& create_back();

    /** Copy this element to the back to the array */
    void push_back(const T& object);

    /** Copy this element to the back to the array */
    void push_back(T&& object) noexcept;

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
    Array<T> m_array;
};

// -----------------

template <typename T>
ObjectArray<T>::ObjectArray() : m_array() {
}

template <typename T>
ObjectArray<T>::ObjectArray(Uint32 size) : m_array(size) {
}

template <typename T>
ObjectArray<T>::~ObjectArray() {
    for (Uint32 i = 0; i < m_array.size(); i++) {
        m_array[i].~T();
    }
}

template <typename T>
bool ObjectArray<T>::isEmpty() const {
    return m_array.isEmpty();
}

template <typename T>
Uint32 ObjectArray<T>::size() const {
    return m_array.size();
}

template <typename T>
bool ObjectArray<T>::resize(Uint32 capacity) {
    if (capacity == 0 || m_array.capacity() == capacity) return false;

    if (void* newData = SDL_malloc(sizeof(T) * capacity)) {
        T* castedNewData = static_cast<T*>(newData);
        if (m_array.m_size != 0) {
            const Uint32 numObjectToMove = SDL_min(m_array.m_size, capacity);
            for (size_t i = 0; i < numObjectToMove; i++) {
                new (castedNewData + i) T(std::move(m_array.m_pData[i]));
            }

            if (capacity < m_array.m_size) {
                for (Uint32 i = numObjectToMove; i < m_array.m_size; i++) {
                    castedNewData[i].~T();
                }
            }
        }

        SDL_free(m_array.m_pData);
        m_array.m_pData = castedNewData;
        m_array.m_capacity = capacity;
        m_array.m_size = SDL_min(m_array.m_size, capacity);
        return true;
    } else {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                     "[ObjectArray::resize] Error allocating memory.");
        return false;
    }
}

template <typename T>
T& ObjectArray<T>::create_back() {
    if (m_array.size() == m_array.capacity()) {
        if (!resize(SDL_max(1, m_array.capacity() * 2))) {
            SDL_assert(false);
        }
    }

    return m_array[m_array.m_size++];
}

template <typename T>
void ObjectArray<T>::push_back(const T& object) {
    new (&create_back()) T(object);
}

template <typename T>
void ObjectArray<T>::push_back(T&& object) noexcept {
    new (&create_back()) T(std::move(object));
}

template <typename T>
T& ObjectArray<T>::operator[](Uint32 index) {
    return m_array[index];
}

template <typename T>
const T& ObjectArray<T>::operator[](Uint32 index) const {
    return m_array[index];
}

template <typename T>
T* ObjectArray<T>::begin() {
    return m_array.begin();
}

template <typename T>
const T* ObjectArray<T>::begin() const {
    return m_array.begin();
}

template <typename T>
T* ObjectArray<T>::end() {
    return m_array.end();
}

template <typename T>
const T* ObjectArray<T>::end() const {
    return m_array.end();
}

template <typename T>
T& ObjectArray<T>::front() {
    return m_array.front();
}

template <typename T>
const T& ObjectArray<T>::front() const {
    return m_array.front();
}

template <typename T>
T& ObjectArray<T>::back() {
    return m_array.back();
}

template <typename T>
const T& ObjectArray<T>::back() const {
    return m_array.back();
}