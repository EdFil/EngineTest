#pragma once

#include <vector>
#include <list>
#include <iostream>
#include <unordered_map>

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
        _handles.reserve(capacity);
        _needsReorder = false;
    }

    Handle createComponent() {
        ComponentIndex index = getFirstAvailableComponentIndex();
        if (index == k_invalidIndex) {
            std::cout << "[System::createComponent] No more components available." << std::endl;
            return k_invalidHandle;
        }

        Handle handle = getReusableHandle();
        if (handle == k_invalidHandle) {
            handle = static_cast<Handle>(_handles.size());
            _handles.push_back(handle);
        }

        ComponentWrapper& component = _components[static_cast<size_t>(index)];
        component.state = ComponentWrapper::State::Used;
        component.handle = handle;
        _handles[handle] = index;
        std::cout << "[System::createComponent] Created I[" << index << "] H[" << handle << "]" << std::endl;

        return handle;
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

        ComponentWrapper& componentWrapper = _components[static_cast<size_t>(index)];
        componentWrapper.handle = k_invalidHandle;
        componentWrapper.state = ComponentWrapper::State::Invalidated;
        _handles[static_cast<size_t>(handle)] = k_invalidHandle;
        std::cout << "[System::releaseComponent] Release I[" << index << "] H[" << handle << "]" << std::endl;

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
                if (componentWrapper.handle != i) {
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
                if (i != _handles[componentWrapper.handle]) {
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
    bool _needsReorder;
    bool _padding[3];

    ComponentIndex getFirstAvailableComponentIndex() const {
        for (size_t i = 0; i < _components.size(); i++) {
            if (_components[i].state != ComponentWrapper::State::Used) {
                return static_cast<ComponentIndex>(i);
            }
        }

        return k_invalidIndex;
    }

    Handle getReusableHandle() const {
        for (size_t i = 0; i < _handles.size(); i++) {
            if (_handles[i] == k_invalidHandle) {
                return static_cast<Handle>(i);
            }
        }

        return k_invalidHandle;
    }
};