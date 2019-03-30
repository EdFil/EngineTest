#pragma once

#include <vector>
#include <list>
#include <iostream>
#include <unordered_map>
#include <cstring>

#define DEBUG 1

using ComponentIndex = int32_t;
using Handle = int32_t;

static const ComponentIndex k_invalidIndex = -1;
static const Handle k_invalidHandle = -1;

template<typename Component>
class System {
public:
    virtual ~System() = default;

    virtual void initWith(size_t capacity) {
        _components.resize(capacity);
        _handles.resize(capacity);
        _needsReorder = false;
        _firstAvailableComponentIndex = 0;
        _firstAvailableHandleIndex = 0;

        memset(&_handles[0], k_invalidHandle, _handles.size() * sizeof _handles[0]);
    }

    Handle createComponent() {
        if (_firstAvailableHandleIndex == k_invalidIndex) {
            std::cout << "[System::createComponent] No more components available." << std::endl;
            return k_invalidHandle;
        }

        if (_firstAvailableHandleIndex == k_invalidHandle) {
            std::cout << "[System::createComponent] No more handles available." << std::endl;
            return k_invalidHandle;
        }

        ComponentWrapper& component = _components[static_cast<size_t>(_firstAvailableComponentIndex)];
        component.state = ComponentWrapper::State::Used;
        component.handle = _firstAvailableHandleIndex;
        _handles[_firstAvailableHandleIndex] = _firstAvailableComponentIndex;
//        std::cout << "[System::createComponent] Created I[" << _handles[_firstAvailableHandleIndex] << "] H[" << component.handle << "]" << std::endl;

        size_t i = static_cast<size_t>(_firstAvailableComponentIndex) + 1;
        _firstAvailableComponentIndex = k_invalidIndex;
        while(i < _components.size()) {
            if (_components[i].state != ComponentWrapper::State::Used) {
                _firstAvailableComponentIndex = static_cast<ComponentIndex>(i);
                break;
            }
            ++i;
        }

        i = static_cast<size_t>(_firstAvailableHandleIndex) + 1;
        _firstAvailableHandleIndex = k_invalidHandle;
        while(i < _handles.size()) {
            if (_handles[i] == k_invalidHandle) {
                _firstAvailableHandleIndex = static_cast<Handle>(i);
                break;
            }
            ++i;
        }
//        std::cout << "[System::createComponent] Next I[" << _firstAvailableHandleIndex << "] H[" << _firstAvailableHandleIndex << "]" << std::endl;

        return component.handle;
    }

    bool releaseComponent(Handle handle) {
        if (handle == k_invalidHandle || static_cast<size_t>(handle) > _handles.size()) {
            std::cout << "[System::releaseComponent] Invalid handle " << handle << std::endl;
            return false;
        }

        ComponentIndex index = _handles[static_cast<size_t>(handle)];
        if (index < 0 || static_cast<size_t>(index) > _components.size()) {
            std::cout << "[System::releaseComponent] Invalid index (" << index << ") in handle (" << handle << ")" << std::endl;
            _handles[static_cast<size_t>(handle)] = k_invalidHandle;
            return false;
        }

        bool isLastUsed = static_cast<size_t >(index) == _components.size() || _components[index + 1].state == ComponentWrapper::State::Unused;

        ComponentWrapper& componentWrapper = _components[static_cast<size_t>(index)];
        componentWrapper.handle = k_invalidHandle;
        componentWrapper.state = isLastUsed ? ComponentWrapper::State::Unused : ComponentWrapper::State::Invalidated;
        _handles[static_cast<size_t>(handle)] = k_invalidHandle;

        if (index < _firstAvailableComponentIndex || _firstAvailableComponentIndex == k_invalidIndex) {
            _firstAvailableComponentIndex = index;
        }

        if (handle < _firstAvailableHandleIndex || _firstAvailableHandleIndex == k_invalidHandle) {
            _firstAvailableHandleIndex = handle;
        }

        _needsReorder |= !isLastUsed;
        std::cout << "[System::releaseComponent] Release I[" << index << "] H[" << handle << "] Needs Reorder[" << _needsReorder << "]" << std::endl;

        return true;
    }

    void checkSystem() {
        std::vector<Handle> checkedHandles;
        for (size_t i = 0; i < _handles.size(); i++) {
            Handle handle = _handles[i];
            if (handle != k_invalidHandle) {
                if (std::find(checkedHandles.cbegin(), checkedHandles.cend(), handle) != checkedHandles.cend()) {
                    abort();
                }
                const ComponentWrapper& componentWrapper = _components[handle];
                if (componentWrapper.handle != static_cast<ComponentIndex>(i)) {
                    abort();
                } else {
                    checkedHandles.emplace_back(handle);
                }
            }
        }

        for (size_t i = 0; i < _components.size(); i++) {
            const ComponentWrapper& componentWrapper = _components[i];
            if (componentWrapper.state == ComponentWrapper::State::Used) {
                if (std::find(checkedHandles.cbegin(), checkedHandles.cend(), i) == checkedHandles.cend()) {
                    abort();
                }
                if (i != static_cast<size_t >(_handles[componentWrapper.handle])) {
                    abort();
                }
            }
        }
    }

    virtual void update(float) = 0;
    virtual void reorder() = 0;

protected:
    struct ComponentWrapper {
        enum class State {
            Unused, Used, Invalidated
        };

        Component component;
        Handle handle = k_invalidHandle;
        State state = State::Unused;
    };

    std::vector<ComponentWrapper> _components;
    std::vector<ComponentIndex> _handles;
    ComponentIndex _firstAvailableComponentIndex = k_invalidIndex;
    Handle _firstAvailableHandleIndex = k_invalidHandle;
    bool _needsReorder = false;
    bool _padding[3];
};