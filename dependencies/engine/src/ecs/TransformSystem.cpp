//#include "TransformSystem.hpp"
//
//#include <cassert>
//
//#include <SDL_log.h>
//
//void TransformSystem::initWithCapacity(int16_t capacity) {
//    if (capacity <= 0) {
//        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[TransformSystem::initWithCapacity] Capacity can not be <= 0");
//    }
//    _nextComponentHandle = 0;
//    _components.resize(capacity);
//
//    for (size_t i = 0; i < _components.size(); i++) {
//        _components[i].nextComponentHandle = i + 1;
//        _components[i].status =  ComponentStatus::Free;
//    }
//}
//
//GlobalHandle TransformSystem::create() {
//	return create(Vector3f());
//}
//
//GlobalHandle TransformSystem::create(const Vector3f& position) {
//    if (_nextComponentHandle >= static_cast<LocalHandle>(_components.size())) {
//		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[TransformSystem::createComponent] Component vector full. Resize not implemented yet");
//        return -1;
//    }
//
//    assert(_components[_nextComponentHandle].status == ComponentStatus::Free);
//
//	const LocalHandle localHandleToReturn = _nextComponentHandle;
//    _nextComponentHandle = _components[localHandleToReturn].nextComponentHandle;
//    _components[localHandleToReturn].status = ComponentStatus::Used;
//
//	_components[localHandleToReturn].component.position = position;
//
//	SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "[TransformSystem::createComponent] Create component with Handle %d next is %d", localHandleToReturn , _nextComponentHandle);
//
//    return transform_system_globals::k_transformHandlePrefix | localHandleToReturn;
//}
//
//void TransformSystem::destroy(const GlobalHandle globalHandle) {
//    if (_nextComponentHandle > static_cast<LocalHandle>(_components.size())) {
//		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[TransformSystem::destroyComponent] Invalid component handle %d", globalHandle);
//        return;
//    }
//
//    const LocalHandle localHandle = static_cast<LocalHandle>(globalHandle);
//    if (_components[localHandle].status == ComponentStatus::Free) {
//		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[TransformSystem::destroyComponent] Component %d was already Free", globalHandle);
//        return;
//    }
//
//    _components[localHandle].status = ComponentStatus::Free;
//    _components[localHandle].nextComponentHandle = _nextComponentHandle;
//    _nextComponentHandle = static_cast<LocalHandle>(localHandle);
//
//	SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "[TransformSystem::destroyComponent] Delete component on Handle %d next is %d", localHandle, _nextComponentHandle);
//}
//
//TransformComponent& TransformSystem::get(const GlobalHandle globalHandle) {
//	const LocalHandle localHandle = static_cast<LocalHandle>(globalHandle);
//	if (localHandle > static_cast<LocalHandle >(_components.size())) {
//		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[TransformSystem::getComponent] Invalid handle %d", localHandle);
//        return transform_system_globals::g_invalidTransformComponent;
//    }
//
//    return _components[localHandle].component;
//}
