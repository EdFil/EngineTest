#pragma once

#include <SDL_assert.h>
#include <SDL_stdinc.h>

template <typename T>
class PODArray {
public:
    PODArray();
    PODArray(Uint32 size);
    ~PODArray();

    /** Returns true is array is empty */
    bool isEmpty() const;

    /** Returns the number of elements in the array */
    Uint32 size() const;

    /** Resize the array so it can fit 'size' elements */
    bool resize(Uint32 size);

	void* data();

    /** Gets array element on index 'index' */
    T& operator[](Uint32 index);

    /** Gets const array element on index 'index' */
    const T& operator[](Uint32 index) const;

private:
    Uint32 _size;
    T* _data;
};

// -----------------

template <typename T>
PODArray<T>::PODArray() : _size(0), _data(nullptr) {
}

template <typename T>
PODArray<T>::PODArray(Uint32 size) : _size(0), _data(nullptr) {
    resize(size);
}

template <typename T>
PODArray<T>::~PODArray() {
    SDL_free(_data);
}

template <typename T>
bool PODArray<T>::isEmpty() const {
    return _size == 0;
}

template <typename T>
Uint32 PODArray<T>::size() const {
    return _size;
}

template <typename T>
bool PODArray<T>::resize(Uint32 size) {
    if (size == 0) {
        return false;
    }

    if (void* newData = SDL_malloc(sizeof(T) * size)) {
        if (_size != 0) {
            SDL_memcpy(newData, _data, sizeof(T) * SDL_min(size, _size));
            SDL_free(_data);
        }

        _data = static_cast<T*>(newData);
        _size = size;
        return true;
    } else {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[PODArray::resize] Error allocating memory.");
        return false;
    }
}

template <typename T>
void* PODArray<T>::data() {
    return _data;
}

template <typename T>
T& PODArray<T>::operator[](Uint32 index) {
    SDL_assert(index < _size);
    return _data[index];
}

template <typename T>
const T& PODArray<T>::operator[](Uint32 index) const {
    SDL_assert(index < _size);
    return _data[index];
}