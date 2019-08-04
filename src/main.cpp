#include <Engine.hpp>
#include <Constants.hpp>

#include <SDL.h>

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

#include <container/PODArray.hpp>

struct TestStruct {
    float health;
    int number;

    // TestStruct() : health(0.0f), number(0) { SDL_Log("Constructor1"); }
    // TestStruct(float health, int number) : health(health), number(number) { SDL_Log("Constructor2"); }
    // TestStruct(const TestStruct&) noexcept { SDL_Log("Copy Constructor"); }
    // TestStruct(TestStruct&&) noexcept { SDL_Log("Move Constructor"); }
    // TestStruct& operator=(const TestStruct&) { SDL_Log("Copy Operator"); return *this; }
    // TestStruct& operator=(TestStruct&&) noexcept { SDL_Log("Move Operator"); return *this; }
    // ~TestStruct() { SDL_Log("Destructor"); }
};

#include <chrono>

int main()
{
    
    {
        auto timepoint = std::chrono::high_resolution_clock::now();
        PODArray<TestStruct> testArray(10000);
        for (int i = 0; i < 10000; i++) {
            testArray.push_back({1.0f, i});
        }
        SDL_Log("Took %ld", std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - timepoint).count());
    }

    {
        auto timepoint = std::chrono::high_resolution_clock::now();
        PODArray<TestStruct> testArray2(10000);
        for (int i = 0; i < 10000; i++) {
            TestStruct& test = testArray2.create_back();
            test.health = 1.0f;
            test.number  = i;
        }
        SDL_Log("Took %ld", std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - timepoint).count());
    }

    {
        auto timepoint = std::chrono::high_resolution_clock::now();
        PODArray<TestStruct> testArray2(10000);
        for (int i = 0; i < 10000; i++) {
            TestStruct& test = testArray2.create_back();
            test = {1.0f, i};
        }
        SDL_Log("Took %ld", std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - timepoint).count());
    }

	srand(time(nullptr));

    // Engine* engine = new Engine();
    // if(engine->initialize()) {
    //     engine->setScene(std::make_unique<MyScene>());
    //     engine->run();
    // }

    // delete engine;

    return 0;
}