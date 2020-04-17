#pragma once

#include <type_traits>

namespace edgine {

    template <typename T>
    class unique_ptr {
    public:
        unique_ptr();
        unique_ptr(T* pData);
        unique_ptr(const unique_ptr<T>&) = delete;
        unique_ptr(unique_ptr<T>&& other) noexcept;
        ~unique_ptr();

        bool operator==(const unique_ptr<T>& other) const;
        void operator=(const unique_ptr<T>&) = delete;
        void operator=(unique_ptr<T>&& other) noexcept;
        T* operator*() const;
        T* operator->() const noexcept;

        void swap(unique_ptr<T>& other);
        void reset(T* pData);

    private:
        T* m_pData;
    };

    template <typename T, class... U>
    unique_ptr<T> make_unique(U&&... u) {
        return unique_ptr(new T(std::forward<U>(u)...));
    }

}  // namespace edgine

template <typename T>
edgine::unique_ptr<T>::unique_ptr() : m_pData(nullptr) {
}

template <typename T>
edgine::unique_ptr<T>::unique_ptr(T* pData) : m_pData(pData) {
}

template <typename T>
edgine::unique_ptr<T>::unique_ptr(unique_ptr&& other) noexcept : m_pData(nullptr) {
    swap(other);
}

template <typename T>
edgine::unique_ptr<T>::~unique_ptr() {
    delete m_pData;
}

template <typename T>
bool edgine::unique_ptr<T>::operator==(const unique_ptr<T>& other) const {
    return m_pData == other.m_pData;
}

template <typename T>
void edgine::unique_ptr<T>::operator=(unique_ptr<T>&& other) noexcept {
    reset(nullptr);
    swap(other);
}

template <typename T>
T* edgine::unique_ptr<T>::operator*() const {
    return m_pData;
}

template <typename T>
T* edgine::unique_ptr<T>::operator->() const noexcept {
    return m_pData;
}

template <typename T>
void edgine::unique_ptr<T>::swap(unique_ptr<T>& other) {
    T* temp = m_pData;
    m_pData = other.m_pData;
    other.m_pData = temp;
}

template <typename T>
void edgine::unique_ptr<T>::reset(T* pData) {
    delete m_pData;
    m_pData = pData;
}