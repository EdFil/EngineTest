#include "ecs/Entity.hpp"
#include "container/Array.hpp"
#include "memory/unique_ptr.hpp"

namespace edgine {
    class EntityManager {
    public:
        EntityManager() = default;
        EntityManager(const EntityManager&) = delete;
        EntityManager(const EntityManager&&) = delete;
        EntityManager& operator=(const EntityManager&) = delete;
        EntityManager& operator=(const EntityManager&&) = delete;

        void addEntity(edgine::unique_ptr<Entity>&& entity);
        void destroyEntity(Entity* entity);

    private:
        edgine::Array<edgine::unique_ptr<Entity>> m_entities;
    };

    template <typename T, typename = std::enable_if<std::is_base_of<Entity, T>::value>, class... U>
    T& make_entity(EntityManager& entityManager, U&&... u) {
        T* entity = new T(std::forward<U>(u)...);
        entityManager.addEntity(unique_ptr<T>(entity));
        return *entity;
    }

}  // namespace edgine

