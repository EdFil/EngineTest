//#pragma once
//
//#include "container/Array.hpp"
//
// using ObjectPoolHandle = Uint32;
//
// namespace object_pool {
//    extern const ObjectPoolHandle k_invalidHandle;
//}
//
// template <typename T>
// class ObjectPool {
//    template <typename T>
//    struct ObjectPoolWrapper {
//        ObjectPoolHandle handle;
//        T object;
//    };
//
//    PODArray<ObjectPoolWrapper<T>> m_objects;
//    ObjectPoolHandle m_nextHandle;
//
// public:
//    ObjectPool();
//    ~ObjectPool();
//
//    void resize(Uint32 capacity);
//    void clear();
//    ObjectPoolHandle getNewHandle();
//    void releaseHandle(ObjectPoolHandle handle);
//    T& operator[](ObjectPoolHandle handle);
//};
//
//// *****************************************
//
// template <typename T>
// ObjectPool<T>::ObjectPool() : m_nextHandle(0) {
//}
//
// template <typename T>
// ObjectPool<T>::~ObjectPool() = default;
//
// template <typename T>
// void ObjectPool<T>::resize(const Uint32 capacity) {
//    Uint32 previousCapacity = m_objects.capacity();
//    m_objects.resize(capacity);
//
//    for (Uint32 i = previousCapacity; i < capacity; i++) {
//        m_objects[i].handle = i + 1;
//    }
//}
//
// template <typename T>
// void ObjectPool<T>::clear() {
//    assert(m_pObjects != nullptr);
//
//    for (Uint32 i = 0; i < m_objects.capacity(); i++) {
//        m_objects[i].handle = i + 1;
//    }
//}
//
// template <typename T>
// ObjectPoolHandle ObjectPool<T>::getNewHandle() {
//    if (m_nextHandle >= m_objects.capacity()) {
//        resize(SDL_max(1, m_objects.capacity() * 2));
//    }
//
//    const ObjectPoolHandle handleToReturn = m_nextHandle;
//    m_nextHandle = m_objects[handleToReturn].handle;
//    m_objects[handleToReturn].handle = object_pool::k_invalidHandle;
//    return handleToReturn;
//}
//
// template <typename T>
// void ObjectPool<T>::releaseHandle(const ObjectPoolHandle handle) {
//    if (handle >= m_objects.capacity() || m_objects[handle].handle !=
//    object_pool::k_invalidHandle) {
//        return;
//    }
//
//    if (m_nextHandle >= m_objects.capacity()) {
//        m_objects[handle].handle = m_objects.capacity() - 1;
//    } else {
//        m_objects[handle].handle = m_nextHandle;
//    }
//
//    m_nextHandle = handle;
//}
//
// template <typename T>
// T& ObjectPool<T>::operator[](const ObjectPoolHandle handle) {
//    return m_objects[handle].object;
//}
