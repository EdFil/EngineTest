//#pragma once
//
//#include <vector>
//#include <map>
//
//#include "math/Vector3f.hpp"
//#include "math/Matrix4f.hpp"
//
//#include "ECS.hpp"
//
//struct TransformInstance {
//    uint32_t id;
//};
//
//struct TransformComponentData {
//    uint32_t size;
//    uint32_t capacity;
//    void* buffer;
//
//    Matrix4f* world;
//    Vector3f* localPosition;
//    Vector3f* localRotation;
//    Vector3f* localScale;
//
//    TransformInstance* parent;
//    TransformInstance* firstChild;
//    TransformInstance* nextSibling;
//    TransformInstance* previousSibling;
//
//    GlobalHandle* entity;
//};
//
//struct TransformComponent {
//	Vector3f position;
//};
//
//struct TransformWrapper {
//	TransformComponent component;
//    LocalHandle nextComponentHandle;
//    ComponentStatus status;
//};
//
//namespace transform_system_globals {
//    static const GlobalHandle k_transformHandlePrefix = 0x00010000;
//    static TransformComponent g_invalidTransformComponent = TransformComponent();
//}
//
//class TransformSystem {
//public:
//    TransformComponentData _data;
//
//
//    std::map<GlobalHandle, TransformInstance> _entityTransformMap;
//
//	TransformSystem() = default;
//	TransformSystem(const TransformSystem&& rhs) = delete;
//	TransformSystem(TransformSystem&& rhs) = delete;
//	TransformSystem& operator=(const TransformSystem& rhs) = delete;
//	TransformSystem& operator=(const TransformSystem&& rhs) = delete;
//
//    void initWithCapacity(int16_t capacity);
//    GlobalHandle create();
//	GlobalHandle create(const Vector3f& position);
//    void destroy(GlobalHandle globalHandle);
//    TransformComponent& get(GlobalHandle globalHandle);
//};
