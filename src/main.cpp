#include <Engine.hpp>
#include <Constants.hpp>

#include <SDL_log.h>

#include <string>
#include <ctime>

#include <Scene.hpp>
#include <math/Matrix4f.hpp>

#define NUM_ENTITIES 100000
class MyScene : public Scene {
public:

    EntityID m_entities[NUM_ENTITIES];

    void onCreated() override {
        _engine->entityManager().initWithCapacity(10);
    }

    void update(float) override {
        for (auto& m_entity : m_entities) {
            m_entity = _engine->entityManager().createEntity();
        }

        EntityID entitiesToDestroy[] = { m_entities[0], m_entities[5], m_entities[9] };
        for (EntityID& entity : entitiesToDestroy) {
            _engine->entityManager().destroyEntity(entity);
        }

        for (auto& m_entity : m_entities) {
            (void)m_entity;
            _engine->entityManager().createEntity();
        }

        _engine->shutdown();
    }

    void onDestroy() override {
        for (auto& m_entity : m_entities) {
            _engine->entityManager().destroyEntity(m_entity);
        }
    }

};

int main()
{
	srand(time(nullptr));

    // Engine* engine = new Engine();
    // if(engine->initialize()) {
    //     engine->setScene(std::make_unique<MyScene>());
    //     engine->run();
    // }

    // delete engine;

    return 0;
}