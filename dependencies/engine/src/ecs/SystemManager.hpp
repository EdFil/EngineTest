#pragma once

#include "container/Array.hpp"
#include "memory/unique_ptr.hpp"

namespace edgine {

    class ISystem;

    class SystemManager {
    public:
        SystemManager() = default;
        SystemManager(const SystemManager& rhs) = delete;
        SystemManager(const SystemManager&& rhs) = delete;
        SystemManager& operator=(const SystemManager& rhs) = delete;
        SystemManager& operator=(const SystemManager&& rhs) = delete;
        ~SystemManager() = default;

        void addSystem(unique_ptr<ISystem>&& system);
        void removeSystem(ISystem* sytem);
        void update(float delta);

    private:
        Array<unique_ptr<ISystem>> m_systems;
    };

}  // namespace edgine