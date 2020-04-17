#pragma once

#include "container/Array.hpp"

namespace edgine {
    template <typename T>
    class Pool {
    public:
        template <typename T>
        struct Handle {
            size_t m_index;
            T m_object;
        };

        typedef T* iterator;
        typedef const T* const_iterator;

        Pool();
        explicit Pool(size_t size);

        ~Pool();

        /** Returns true is array is empty */
        bool isEmpty() const;

        /** Returns the number of elements in the array */
        size_t size() const;

        /** Returns the number of elements in the array */
        size_t capacity() const;

        bool reserve(size_t size);

        Handle* getObject();
        void returnObject(Handle* handle);

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
        Array<Handle<T>> m_array;
        size_t m_size;
        size_t m_nextIndex;

        bool alloc(size_t capacity);
    };

}  // namespace edgine

// -----------------

template <typename T>
edgine::Pool<T>::Pool() : m_array(), m_nextIndex(0) {
}

template <typename T>
edgine::Pool<T>::Pool(size_t size) : m_array(size), m_nextIndex(0) {
}

template <typename T>
edgine::Pool<T>::~Pool() {

}

template <typename T>
bool edgine::Pool<T>::isEmpty() const {
    return m_array.isEmpty();
}

template <typename T>
size_t edgine::Pool<T>::size() const {
    return m_size;
}

template <typename T>
size_t edgine::Pool<T>::capacity() const {
    return m_array.capacity();
}

template <typename T>
bool edgine::Pool<T>::reserve(size_t capacity) {
    return m_array.reserve();
}

template <typename T>
void edgine::Pool<T>::push_back(const T& object) {
    create_back() = object;
}

template <typename T>
void edgine::Pool<T>::push_back(T&& object) {
    create_back() = std::move(object);
}

template <typename T>
T& edgine::Pool<T>::operator[](size_t index) {
    SDL_assert(index < m_size);
    return m_pData[index];
}

template <typename T>
const T& edgine::Pool<T>::operator[](size_t index) const {
    SDL_assert(index < m_size);
    return m_pData[index];
}

template <typename T>
typename edgine::Pool<T>::iterator edgine::Pool<T>::begin() {
    return m_pData;
}

template <typename T>
typename edgine::Pool<T>::const_iterator edgine::Pool<T>::begin() const {
    return m_pData;
}

template <typename T>
typename edgine::Pool<T>::iterator edgine::Pool<T>::end() {
    return m_pData + m_size;
}

template <typename T>
typename edgine::Pool<T>::const_iterator edgine::Pool<T>::end() const {
    return m_pData + m_size;
}

template <typename T>
T& edgine::Pool<T>::front() {
    SDL_assert(m_size > 0);
    return m_pData[0];
}

template <typename T>
const T& edgine::Pool<T>::front() const {
    SDL_assert(m_size > 0);
    return m_pData[0];
}

template <typename T>
T& edgine::Pool<T>::back() {
    SDL_assert(m_size > 0);
    return m_pData[m_size - 1];
}

template <typename T>
const T& edgine::Pool<T>::back() const {
    SDL_assert(m_size > 0);
    return m_pData[m_size - 1];
}

template <typename T>
typename edgine::Pool<T>::iterator edgine::Pool<T>::find(const T& object) const {
    for (size_t i = 0; i < m_size; i++) {
        if (m_pData[i] == object) {
            return m_pData + i;
        }
    }

    return nullptr;
}

template <typename T>
bool edgine::Pool<T>::erase(Array<T>::iterator object) {
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
bool edgine::Pool<T>::alloc(size_t capacity) {
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