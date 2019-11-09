#pragma once

#include "container/Array.hpp"

template <typename T>
class PODVector {
public:
    PODVector();
    PODVector(Uint32 size);
    ~PODVector();

    /** Returns true is array is empty */
    bool isEmpty() const;

    /** Returns the number of elements in the vector */
    Uint32 size() const;

    /** Returns the number of allocated elements in the vector */
    Uint32 capacity() const;

    /** Resize the array so it can fit 'size' elements */
    bool resize(Uint32 size);

    T& create_back();

    void push_back(const T& object);

    void erase(const T& object);

    void fast_erase(const T& object);

    /** Gets array element on index 'index' */
    T& operator[](Uint32 index);

    /** Gets const array element on index 'index' */
    const T& operator[](Uint32 index) const;

private:
    Uint32 _size;
    Array<T> _vector;
};

// -----------------

template <typename T>
PODVector<T>::PODVector() : _size(0) {
}

template <typename T>
PODVector<T>::PODVector(Uint32 capacity) : _size(0) {
    resize(capacity);
}

template <typename T>
PODVector<T>::~PODVector() {
}

template <typename T>
bool PODVector<T>::isEmpty() const {
    return _size == 0;
}

template <typename T>
Uint32 PODVector<T>::size() const {
    return _size;
}

template <typename T>
Uint32 PODVector<T>::capacity() const {
    return _vector.size();
}

template <typename T>
bool PODVector<T>::resize(Uint32 capacity) {
    return _vector.resize(capacity);
}

template <typename T>
T& PODVector<T>::create_back() {
    if (_size == _vector.size()) {
        resize(_vector.size() * 2);
    }

    return _vector[_size++];
}

template <typename T>
void PODVector<T>::push_back(const T& object) {
    if (_size >= _vector.size()) {
        resize(SDL_max(1, _vector.size() * 2));
    }

    _vector[_size++] = object;
}

template <typename T>
void PODVector<T>::erase(const T& object) {
    for (Uint32 i = 0; i < _vector.size(); i++) {
        if (_vector[i] == object) {
            if (i != _vector.size() - 1) {
                const size_t moveSize = _vector.size() - i + 1 * sizeof(T);
                SDL_memcpy(&_vector[0] + i, &_vector[0] + i + 1, moveSize);
            }

            --_size;
            return;
        }
    }
}

template <typename T>
void PODVector<T>::fast_erase(const T& object) {
    for (Uint32 i = 0; i < _vector.size(); i++) {
        if (_vector[i] == object) {
            if (i != _vector.size() - 1) {
                _vector[i] = _vector[_size - 1];
            }

            --_size;
            return;
        }
    }
}

template <typename T>
T& PODVector<T>::operator[](Uint32 index) {
    SDL_assert(index < _size);
    return _vector[index];
}

template <typename T>
const T& PODVector<T>::operator[](Uint32 index) const {
    SDL_assert(index < _size);
    return _vector[index];
}