#pragma once

#include <SDL_assert.h>
#include <SDL_log.h>
#include <SDL_stdinc.h>

#include <utility>

template <typename T, bool isObject = true>
class Array {
public:
    Array();
    Array(Uint32 size);
    ~Array();

    /** Returns true is array is empty */
    bool isEmpty() const;

    /** Returns the number of elements in the array */
    Uint32 size() const;

    /** Resize the array so it can fit 'size' elements */
    bool resize(Uint32 size);

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
    Uint32 _size;
    T* _data;
};

// -----------------

template <typename T, bool isObject>
Array<T, isObject>::Array() : _size(0), _data(nullptr) {
}

template <typename T, bool isObject>
Array<T, isObject>::Array(Uint32 size) : _size(0), _data(nullptr) {
    resize(size);
}

template <typename T, bool isObject>
Array<T, isObject>::~Array() {
    if (isObject) {
        for (Uint32 i = 0; i < _size; i++) {
            _data[i].~T();
        }
    }

    SDL_free(_data);
}

template <typename T, bool isObject>
bool Array<T, isObject>::isEmpty() const {
    return _size == 0;
}

template <typename T, bool isObject>
Uint32 Array<T, isObject>::size() const {
    return _size;
}

template <typename T, bool isObject>
bool Array<T, isObject>::resize(Uint32 size) {
    if (size == 0 || _size == size) return false;

    if (void* newData = SDL_malloc(sizeof(T) * size)) {
        T* castedNewData = static_cast<T*>(newData);
        if (_size != 0) {
            if (isObject) {
                const Uint32 numObjectToMove = SDL_min(_size, size);
                for (size_t i = 0; i < numObjectToMove; i++) {
                    new (castedNewData + i) T(std::move(_data[i]));
                }

                if (size < _size) {
                    for (Uint32 i = numObjectToMove; i < _size; i++) {
                        castedNewData[i].~T();
                    }
                } else {
                    for (size_t i = numObjectToMove; i < size; i++) {
                        new (castedNewData + i) T();
                    }
                }
            } else {
                SDL_memcpy(newData, _data, sizeof(T) * SDL_min(size, _size));
                SDL_free(_data);
            }
        } else if (isObject) {
            for (size_t i = 0; i < size; i++) {
                new (castedNewData + i) T();
            }
        }

        _data = castedNewData;
        _size = size;
        return true;
    } else {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[PODArray::resize] Error allocating memory.");
        return false;
    }
}

template <typename T, bool isObject>
T& Array<T, isObject>::operator[](Uint32 index) {
    SDL_assert(index < _size);
    return _data[index];
}

template <typename T, bool isObject>
const T& Array<T, isObject>::operator[](Uint32 index) const {
    SDL_assert(index < _size);
    return _data[index];
}

template <typename T, bool isObject>
T* Array<T, isObject>::begin() {
    return _data;
}

template <typename T, bool isObject>
const T* Array<T, isObject>::begin() const {
    return _data;
}

template <typename T, bool isObject>
T* Array<T, isObject>::end() {
    return _data + _size;
}

template <typename T, bool isObject>
const T* Array<T, isObject>::end() const {
    return _data + _size;
}

template <typename T, bool isObject>
T& Array<T, isObject>::front() {
    SDL_assert(_size > 0);
    return _data[0];
}

template <typename T, bool isObject>
const T& Array<T, isObject>::front() const {
    SDL_assert(_size > 0);
    return _data[0];
}

template <typename T, bool isObject>
T& Array<T, isObject>::back() {
    SDL_assert(_size > 0);
    return _data[_size - 1];
}

template <typename T, bool isObject>
const T& Array<T, isObject>::back() const {
    SDL_assert(_size > 0);
    return _data[_size - 1];
}