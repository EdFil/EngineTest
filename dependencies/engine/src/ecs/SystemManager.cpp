 #include "ecs/SystemManager.hpp"

#include "ecs/ISystem.hpp"

 void edgine::SystemManager::addSystem(unique_ptr<ISystem>&& pSystem) {
    m_systems.push_back(std::move(pSystem));
 }

 void edgine::SystemManager::removeSystem(ISystem* pSystem) {
     m_systems.erase(m_systems.find(pSystem));
 }

 void edgine::SystemManager::update(float delta) {
     for (auto& system : m_systems) {
         system->update(delta);
     }
 }