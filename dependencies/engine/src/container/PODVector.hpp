// #include <SDL_stdinc.h>

// template <typename T>
// class Vector {
// public:
//     Vector();
//     ~Vector();

//     bool empty() const;
//     int size() const;
//     int capacity() const;
//     T& operator[](Uint32 index);
//     const T& operator[](Uint32 index) const;

//     void clear();
//     void reserve(Uint32 newCapacity);
//     void resize(Uint32 newSize);

//     void push_back(const T& v);
//     void pop_back();
//     void push_front(const T& v);
//     T* erase(const T* it);
//     T* fast_erase(const T* it);
//     T* insert(const T* it, const T& v);
//     bool contains(const T& v) const;

// private:
//     Uint32 m_size;
//     Uint32 m_capacity;
//     T* m_pData;
// };

// template <typename T>
// Vector<T>::Vector() : m_size(0), m_capacity(0), m_pData(0) {}

// template <typename T>
// Vector<T>::~Vector() {
//     SDL_free(m_pData);
// }

// template <typename T>
// bool Vector<T>::empty() const {
//     return m_size == 0;
// }

// template <typename T>
// int Vector<T>::size() const {
//     return m_size;
// }

// template <typename T>
// int Vector<T>::capacity() const {
//     return m_capacity;
// }

// template <typename T>
// T& Vector<T>::operator[](Uint32 index) {
//     SDL_assert(index < m_size);
//     return m_pData[index];
// }

// template <typename T>
// const T& Vector<T>::operator[](Uint32 index) const {
//     SDL_assert(index < m_size);
//     return m_pData[index];
// }

// template <typename T>
// void Vector<T>::clear() {
//     SDL_free(m_pData);
//     m_size = m_capacity = 0;
//     m_pData = nullptr;
// }

// template <typename T>
// void Vector<T>::reserve(Uint32 newCapacity) {
//     if (newCapacity <= m_capacity) return;

//     if (void* newData = SDL_realloc(m_pData, sizeof(T) * newCapacity)) {
//         m_pData = (T*)newData;
//         m_capacity = newCapacity;
//         SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION,
//                     "[Vector::reserve] (re)allocating memory...");
//     } else {
//         SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
//                      "[Vector::reserve] Error (re)allocating memory...");
//     }
// }

// template <typename T>
// void Vector<T>::resize(Uint32 newSize) {
//     if (newSize > m_capacity) reserve(newSize);
//     m_size = newSize;
// }

// template <typename T>
// void Vector<T>::push_back(const T& v) {
//     if (m_size == m_capacity) reserve(_grow_capacity(m_size + 1));
//     memcpy(&m_pData[m_size], &v, sizeof(v));
//     m_size++;
// }

// template <typename T>
// void pop_back() {
//     SDL_assert(m_size > 0);
//     m_size--;
// }

// template <typename T>
// void Vector<t>::push_front(const T& v) {
//     if (m_size == 0)
//         push_back(v);
//     else
//         insert(m_pData, v);
// }

// template <typename T>
// T* Vector<T>::erase(const T* it) {
//     SDL_assert(it >= m_pData && it < m_pData + m_size);
//     const ptrdiff_t off = it - m_pData;
//     memmove(m_pData + off, m_pData + off + 1,
//             ((size_t)m_size - (size_t)off - 1) * sizeof(T));
//     m_size--;
//     return m_pData + off;
// }

// template <typename T>
// T* Vector<T>::fast_erase(const T* it) {
//     SDL_assert(it >= m_pData && it < m_pData + m_size);
//     const ptrdiff_t off = it - m_pData;
//     if (it < m_pData + m_size - 1)
//         memcpy(m_pData + off, m_pData + m_size - 1, sizeof(T));
//     m_size--;
//     return m_pData + off;
// }

// template <typename T>
// T* Vector<T>::insert(const T* it, const T& v) {
//     SDL_assert(it >= m_pData && it <= m_pData + Size);
//     const ptrdiff_t off = it - Data;
//     if (Size == Capacity) reserve(_grow_capacity(Size + 1));
//     if (off < (int)Size)
//         memmove(m_pData + off + 1, m_pData + off,
//                 ((size_t)Size - (size_t)off) * sizeof(T));
//     memcpy(&m_pData[off], &v, sizeof(v));
//     Size++;
//     return m_pData + off;
// }

// template <typename T>
// bool Vector<T>::contains(const T& v) const {
//     const T* data = Data;
//     const T* data_end = Data + Size;
//     while (data < data_end)
//         if (*data++ == v) return true;
//     return false;
// }