#pragma once

#include <SDL_assert.h>
#include <SDL_stdinc.h>
#include <utility>

/** Fixed length array where the data is part of the Array's class size */
template <typename T, uint32_t N>
class FixedArray {
public:
    /** Returns true is array is empty */
    bool isEmpty() const { return m_size == 0; }

    /** Returns the number of elements in the array */
    uint32_t size() const { return m_size; }

    /** Returns the maximum number of elements this array can hold */
    uint32_t capacity() const { return N; }

    /** Copy this element to the back to the array */
    T* push_back(const T& object) {
        if (m_size >= N) return nullptr;
        m_pData[++m_size] = object;
    }

    /** Move this element to the back to the array */
    void push_back(T&& object) noexcept {
        if (m_size >= N) return nullptr;
        m_pData[++m_size] = std::move(object);
    }

    /** Create a new element at back to the array using the constructor */
    template <typename... Ts>
    T* emplace_back(Ts&&... args) {
        if (m_size >= N) return nullptr;
        return new (&m_pData[m_size++]) T(std::forward<Ts>(args)...);
    }

    /** Remove all elements starting from the element provided. erase(std::remove()) idiom */
    void erase(T* value) {
        if (value > m_pData) {
            uint32_t newIndex = (uint32_t)(value - m_pData);
            if (newIndex < N) {
                m_size = newIndex;
            }
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
    const T* cbegin() const { return m_pData; }

    /** Gets a pointer to the end of the array */
    T* end() { return m_pData + m_size; }

    /** Gets a const pointer to the end of the array */
    const T* cend() const { return m_pData + m_size; }

    /** Gets a reference to the beginning of the array */
    T& front() {
        SDL_assert(m_size > 0);
        return m_pData[0];
    }

    /** Gets a const reference to the beginning of the array */
    const T& front() const {
        SDL_assert(m_size > 0);
        return m_pData[0];
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
    T m_pData[N];
};