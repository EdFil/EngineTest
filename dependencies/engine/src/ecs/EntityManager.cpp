 #include "EntityManager.hpp"

void edgine::EntityManager::addEntity(Entity* entity) {
    m_entities.push_back(entity);
}

void edgine::EntityManager::addEntity(edgine::unique_ptr<Entity>&& entity) {
    m_entities.push_back(std::move(entity));
}

void edgine::EntityManager::destroyEntity(Entity* entity) {
    m_entities.erase(m_entities.find(entity));
}
