#pragma once

#include <SDL_assert.h>
#include <SDL_log.h>
#include <SDL_stdinc.h>

#include <new>
#include <utility>

namespace edgine {

    template <typename T>
    class Array {
    public:
        typedef T* iterator;
        typedef const T* const_iterator;

        Array();
        explicit Array(size_t size);

        ~Array();

        /** Returns true is array is empty */
        bool isEmpty() const;

        /** Returns the number of elements in the array */
        size_t size() const;

        /** Returns the number of elements in the array */
        size_t capacity() const;

        /** Resize the array so it can fit 'size' elements */
        bool resize(size_t size);

        bool reserve(size_t size);

        /** Create a element on the back and return a reference to it */
        T& create_back();

        /** Copy this element to the back to the array */
        void push_back(const T& object);

        /** Move this element to the back to the array */
        void push_back(T&& object);

        /** Gets array element on index 'index' */
        T& operator[](size_t index);

        /** Gets const array element on index 'index' */
        const T& operator[](size_t index) const;

        /** Gets a pointer to the beginning of the array */
        iterator begin();

        /** Gets a const pointer to the beginning of the array */
        const_iterator begin() const;

        /** Gets a pointer to the end of the array */
        iterator end();

        /** Gets a const pointer to the end of the array */
        const_iterator end() const;

        /** Gets a reference to the beginning of the array */
        T& front();

        /** Gets a const reference to the beginning of the array */
        const T& front() const;

        /** Gets a reference to the end of the array */
        T& back();

        /** Gets a const reference to the end of the array */
        const T& back() const;

        iterator find(const T& object) const;

        bool erase(iterator object);

    private:
        size_t m_size;
        size_t m_capacity;
        T* m_pData;

        bool alloc(size_t capacity);
    };

}  // namespace edgine

// -----------------

template <typename T>
edgine::Array<T>::Array() : m_size(0), m_capacity(0), m_pData(nullptr) {
}

template <typename T>
edgine::Array<T>::Array(size_t size) : m_size(0), m_capacity(0), m_pData(nullptr) {
    reserve(size);
}

template <typename T>
edgine::Array<T>::~Array() {
    for (size_t i = 0; i < m_size; i++) {
        m_pData[i].~T();
    }
    SDL_free(m_pData);
}

template <typename T>
bool edgine::Array<T>::isEmpty() const {
    return m_size == 0;
}

template <typename T>
size_t edgine::Array<T>::size() const {
    return m_size;
}

template <typename T>
size_t edgine::Array<T>::capacity() const {
    return m_capacity;
}

template <typename T>
bool edgine::Array<T>::reserve(size_t capacity) {
    if (m_capacity >= capacity) {
        return true;
    }

    return alloc(capacity);
}

template <typename T>
bool edgine::Array<T>::resize(size_t capacity) {
    if (capacity == 0 || m_capacity == capacity) return false;

    if (void* newData = SDL_malloc(sizeof(T) * capacity)) {
        T* castedNewData = static_cast<T*>(newData);
        if (m_size != 0) {
            const size_t numObjectToMove = SDL_min(m_size, capacity);
            for (size_t i = 0; i < numObjectToMove; i++) {
                new (m_pData) T();
            }

            if (capacity < m_size) {
                for (size_t i = numObjectToMove; i < m_size; i++) {
                    castedNewData[i].~T();
                }
            } else {
                for (size_t i = numObjectToMove; i < capacity; i++) {
                    new (castedNewData + i) T();
                }
            }
        }

        SDL_free(m_pData);
        m_pData = castedNewData;
        m_size = m_capacity = capacity;
        return true;
    } else {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                     "[Array::resize] Error allocating memory.");
        return false;
    }
}

template <typename T>
T& edgine::Array<T>::create_back() {
    if (m_size == m_capacity) {
        if (!reserve(SDL_max(1, m_capacity * 2))) {
            SDL_assert(false);
        }
    }

    // new (m_pData + m_size) T();
    return m_pData[m_size++];
}

template <typename T>
void edgine::Array<T>::push_back(const T& object) {
    create_back() = object;
}

template <typename T>
void edgine::Array<T>::push_back(T&& object) {
    create_back() = std::move(object);
}

template <typename T>
T& edgine::Array<T>::operator[](size_t index) {
    SDL_assert(index < m_size);
    return m_pData[index];
}

template <typename T>
const T& edgine::Array<T>::operator[](size_t index) const {
    SDL_assert(index < m_size);
    return m_pData[index];
}

template <typename T>
typename edgine::Array<T>::iterator edgine::Array<T>::begin() {
    return m_pData;
}

template <typename T>
typename edgine::Array<T>::const_iterator edgine::Array<T>::begin() const {
    return m_pData;
}

template <typename T>
typename edgine::Array<T>::iterator edgine::Array<T>::end() {
    return m_pData + m_size;
}

template <typename T>
typename edgine::Array<T>::const_iterator edgine::Array<T>::end() const {
    return m_pData + m_size;
}

template <typename T>
T& edgine::Array<T>::front() {
    SDL_assert(m_size > 0);
    return m_pData[0];
}

template <typename T>
const T& edgine::Array<T>::front() const {
    SDL_assert(m_size > 0);
    return m_pData[0];
}

template <typename T>
T& edgine::Array<T>::back() {
    SDL_assert(m_size > 0);
    return m_pData[m_size - 1];
}

template <typename T>
const T& edgine::Array<T>::back() const {
    SDL_assert(m_size > 0);
    return m_pData[m_size - 1];
}

template <typename T>
typename edgine::Array<T>::iterator edgine::Array<T>::find(const T& object) const {
    for (size_t i = 0; i < m_size; i++) {
        if (m_pData[i] == object) {
            return m_pData + i;
        }
    }

    return nullptr;
}

template <typename T>
bool edgine::Array<T>::erase(Array<T>::iterator object) {
    if (object != nullptr) {
        size_t index = std::ptrdiff_t(object - begin());

        if (index >= 0 && index < m_size) {
            object->~T();
            if (m_size > 0) {
                for (index = index + 1; index < m_size; index++) {
                    m_pData[index - 1] = std::move(m_pData[index]);
                }
            }

            m_size--;
            return true;
        }
    }

    return false;
}

template <typename T>
bool edgine::Array<T>::alloc(size_t capacity) {
    if (capacity == 0 || m_capacity == capacity) return false;

    if (void* newData = SDL_malloc(sizeof(T) * capacity)) {
        T* castedNewData = static_cast<T*>(newData);
        if (m_size != 0) {
            for (size_t i = 0; i < m_size; i++) {
                new (castedNewData + i) T(std::move(m_pData[i]));
            }
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