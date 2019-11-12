//#pragma once
//
//#include "container/Array.hpp"
//
//template <typename T, bool isObject = true>
//class PODVector {
//public:
//    PODVector();
//    PODVector(Uint32 size);
//    ~PODVector();
//
//    /** Returns true is array is empty */
//    bool isEmpty() const;
//
//    /** Returns the number of elements in the vector */
//    Uint32 size() const;
//
//    /** Returns the number of allocated elements in the vector */
//    Uint32 capacity() const;
//
//    /** Allocate enough memory for size elements */
//    bool reserve(Uint32 size);
//
//    T& create_back();
//
//    void push_back(const T& object);
//
//    void erase(const T& object);
//
//    void fast_erase(const T& object);
//
//    /** Gets array element on index 'index' */
//    T& operator[](Uint32 index);
//
//    /** Gets const array element on index 'index' */
//    const T& operator[](Uint32 index) const;
//
//private:
//    Uint32 _size = 0;
//    Uint32 _capacity = 0;
//    T* _data = nullptr;
//};
//
//// -----------------
//
//template <typename T, bool isObject>
//PODVector<T, isObject>::PODVector() {
//}
//
//template <typename T, bool isObject>
//PODVector<T, isObject>::PODVector(Uint32 capacity) {
//    reserve(capacity);
//}
//
//template <typename T, bool isObject>
//PODVector<T, isObject>::~PODVector() {
//    if (isObject) {
//        for (Uint32 i = 0; i < _size; i++) {
//            _data[i].~T();
//		}
//	}
//
//	SDL_free(_data);
//}
//
//template <typename T, bool isObject>
//bool PODVector<T, isObject>::isEmpty() const {
//    return _size == 0;
//}
//
//template <typename T, bool isObject>
//Uint32 PODVector<T, isObject>::size() const {
//    return _size;
//}
//
//template <typename T, bool isObject>
//Uint32 PODVector<T, isObject>::capacity() const {
//    return _capacity;
//}
//
//template <typename T, bool isObject>
//bool PODVector<T, isObject>::reserve(Uint32 capacity) {
//    if (capacity <= capacity) return;
//
//    if (void* newData = SDL_malloc(sizeof(T) * capacity)) {
//        T* castedNewData = static_cast<T*>(newData);
//        if (_size != 0) {
//            if (isObject) {
//                for (size_t i = 0; i < _size; i++) {
//                    new (castedNewData + i) T(std::move(_data[i]));
//                }
//            } else {
//                SDL_memcpy(newData, _data, sizeof(T) * _size);
//            }
//
//            SDL_free(_data);
//        } else if (isObject) {
//            for (size_t i = 0; i < size; i++) {
//                new (castedNewData + i) T();
//            }
//        }
//
//        _data = castedNewData;
//        _size = size;
//        return true;
//    } else {
//        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[PODArray::resize] Error allocating memory.");
//        return false;
//    }
//}
//
//template <typename T, bool isObject>
//T& PODVector<T, isObject>::create_back() {
//    if (_size == _vector.size()) {
//        resize(_vector.size() * 2);
//    }
//
//    return _vector[_size++];
//}
//
//template <typename T, bool isObject>
//void PODVector<T, isObject>::push_back(const T& object) {
//    if (_size >= _vector.size()) {
//        resize(SDL_max(1, _vector.size() * 2));
//    }
//
//    _vector[_size++] = object;
//}
//
//template <typename T, bool isObject>
//void PODVector<T, isObject>::erase(const T& object) {
//    for (Uint32 i = 0; i < _vector.size(); i++) {
//        if (_vector[i] == object) {
//            if (i != _vector.size() - 1) {
//                const size_t moveSize = _vector.size() - i + 1 * sizeof(T);
//                SDL_memcpy(&_vector[0] + i, &_vector[0] + i + 1, moveSize);
//            }
//
//            --_size;
//            return;
//        }
//    }
//}
//
//template <typename T, bool isObject>
//void PODVector<T, isObject>::fast_erase(const T& object) {
//    for (Uint32 i = 0; i < _vector.size(); i++) {
//        if (_vector[i] == object) {
//            if (i != _vector.size() - 1) {
//                _vector[i] = _vector[_size - 1];
//            }
//
//            --_size;
//            return;
//        }
//    }
//}
//
//template <typename T, bool isObject>
//T& PODVector<T, isObject>::operator[](Uint32 index) {
//    SDL_assert(index < _size);
//    return _vector[index];
//}
//
//template <typename T, bool isObject>
//const T& PODVector<T, isObject>::operator[](Uint32 index) const {
//    SDL_assert(index < _size);
//    return _vector[index];
//}