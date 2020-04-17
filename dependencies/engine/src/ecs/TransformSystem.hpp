#pragma once

#include "container/Array.hpp"
#include "ecs/EntityManager.hpp"
#include "ecs/ISystem.hpp"
#include "ecs/IComponent.hpp"
#include "math/Vector3f.hpp"

namespace edgine {

    struct TransformComponent final : public IComponent {
        Vector3f m_localPosition;
    };

    struct TransformHandle {
        size_t index;
    };

    class TransformSystem final : public ISystem {
    public:
        TransformSystem();
        TransformSystem(const TransformSystem& rhs) = delete;
        TransformSystem(const TransformSystem&& rhs) = delete;
        TransformSystem& operator=(const TransformSystem& rhs) = delete;
        TransformSystem& operator=(const TransformSystem&& rhs) = delete;

        TransformHandle createComponent();
        TransformComponent* getComponent(const TransformHandle& handle);
        void destroyComponent(const TransformHandle& handle);

        // ISystem
        void update(float delta) override {}

    private:
        union TransformData {
            size_t nextHandle;
            TransformComponent transformComponent;
        };

        Array<TransformComponent> m_components;
        Array<size_t> m_componentHandles;
        size_t m_nextHandle;

    };

}  // namespace edgine