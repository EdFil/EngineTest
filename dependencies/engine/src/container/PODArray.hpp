#include <SDL_stdinc.h>

template <typename T>
class PODArray {
public:
    PODArray();
    PODArray(Uint32 capacity);
    ~PODArray();

    /** Returns true is array is empty */
    bool isEmpty() const;

    /** Returns the number of elements in the array */
    Uint32 size() const;

    /** Returns the number of elements allowed without reallocating memory */
    Uint32 capacity() const;

    /** Resize the array so it can fit 'size' elements */
    void resize(Uint32 size);

    /**  */
    T& create_back();

    /** Copy item to end of the array. Can reallocate memory if already full */
    void push_back(const T& item);

    /** Decreases the size of the array by 1 */
    void pop_back();

    /** Sets size of array to 0 */
    void clear();

    /** Gets array element on index 'index' */
    T& operator[](Uint32 index);

    /** Gets const array element on index 'index' */
    const T& operator[](Uint32 index) const;

private:
    Uint32 _capacity;
    Uint32 _size;
    T* _data;
};

// -----------------

template <typename T>
PODArray<T>::PODArray() : _capacity(0), _size(0), _data(nullptr) {}

template <typename T>
PODArray<T>::PODArray(Uint32 capacity)
  : _capacity(0), _size(0), _data(nullptr) {
    resize(capacity);
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
Uint32 PODArray<T>::capacity() const {
    return _capacity;
}

template <typename T>
void PODArray<T>::resize(Uint32 size) {
    if (size == 0) {
        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION,
                    "[PODArray::resize] Resize to 0. Deleting memory...");
        SDL_free(_data);
        _data = nullptr;
        _size = _capacity = 0;

    } else if (void* newData = SDL_realloc(_data, sizeof(T) * size)) {
        _data = (T*)newData;
        _capacity = size;
        _size = SDL_min(size, _size);
        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION,
                    "[PODArray::resize] (re)allocating memory...");
    } else {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                     "[PODArray::resize] Error (re)allocating memory...");
    }
}

template <typename T>
T& PODArray<T>::create_back() {
    if (_size == _capacity) {
        resize(SDL_max(_capacity * 2, 1));
    }

    _size++;
    return _data[_size - 1];
}

template <typename T>
void PODArray<T>::push_back(const T& item) {
    if (_size == _capacity) {
        resize(SDL_max(_capacity * 2, 1));
    }

    _data[_size] = item;
    _size++;
}

template <typename T>
void PODArray<T>::pop_back() {
    if (_size != 0) {
        --_size;
    }
}

template <typename T>
void PODArray<T>::clear() {
    _size = 0;
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