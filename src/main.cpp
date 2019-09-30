#include <Constants.hpp>
#include <Engine.hpp>

#include <SDL.h>

#include <Scene.hpp>
#include <core/HashString.hpp>
#include <ctime>
#include <math/Matrix4f.hpp>

#define NUM_ENTITIES 100000
class MyScene : public Scene {
public:
    EntityID m_entities[NUM_ENTITIES];

    void onCreated() override { _engine->entityManager().initWithCapacity(10); }

    void update(float) override {
        for (auto& m_entity : m_entities) {
            m_entity = _engine->entityManager().createEntity();
        }

        EntityID entitiesToDestroy[] = {m_entities[0], m_entities[5], m_entities[9]};
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
    // TestStruct(float health, int number) : health(health), number(number) {
    // SDL_Log("Constructor2"); } TestStruct(const TestStruct&) noexcept {
    // SDL_Log("Copy Constructor"); } TestStruct(TestStruct&&) noexcept {
    // SDL_Log("Move Constructor"); } TestStruct& operator=(const TestStruct&) {
    // SDL_Log("Copy Operator"); return *this; } TestStruct&
    // operator=(TestStruct&&) noexcept { SDL_Log("Move Operator"); return
    // *this; } ~TestStruct() { SDL_Log("Destructor"); }
};

#include <chrono>

void testArray() {
    const unsigned kInitialSize = 1000;
    const unsigned kNumElems = 1000;
    {
        auto timepoint = std::chrono::high_resolution_clock::now();
        PODArray<TestStruct> testArray(kInitialSize);
        for (unsigned i = 0; i < kNumElems; i++) {
            testArray.push_back({1.0f, (int)i});
        }
        SDL_Log("Took %ld", std::chrono::duration_cast<std::chrono::nanoseconds>(
                                std::chrono::high_resolution_clock::now() - timepoint)
                                .count());
    }

    {
        auto timepoint = std::chrono::high_resolution_clock::now();
        PODArray<TestStruct> testArray2(kInitialSize);
        for (unsigned i = 0; i < kNumElems; i++) {
            TestStruct& test = testArray2.create_back();
            test.health = 1.0f;
            test.number = i;
        }
        SDL_Log("Took %ld", std::chrono::duration_cast<std::chrono::nanoseconds>(
                                std::chrono::high_resolution_clock::now() - timepoint)
                                .count());
    }

    {
        auto timepoint = std::chrono::high_resolution_clock::now();
        PODArray<TestStruct> testArray2(kInitialSize);
        for (unsigned i = 0; i < kNumElems; i++) {
            TestStruct& test = testArray2.create_back();
            test = {1.0f, (int)i};
        }
        SDL_Log("Took %ld", std::chrono::duration_cast<std::chrono::nanoseconds>(
                                std::chrono::high_resolution_clock::now() - timepoint)
                                .count());
    }
}

#include <core/String.hpp>

#define PRINT_STRING(__STRING__)                                                         \
    SDL_Log("Data:%s, Capacity:%d, Length:%d", __STRING__.data(), __STRING__.capacity(), \
            __STRING__.length());

void testString() {
    {
        String string;
        PRINT_STRING(string)
    }

    {
        String string("");
        PRINT_STRING(string)
    }

    {
        String string("This is a string");
        PRINT_STRING(string)
        string = "This is a bigger string";
        PRINT_STRING(string)
        string = "Small string";
        PRINT_STRING(string)
    }

    return;
}

void testHashString() {
    {
        HashString hashString = CreateHashString("This is a test");
        HashString hashString2 = CreateHashString("This is a test");
        HashString hashString3 = CreateHashString("This is a second test");

        SDL_assert(hashString == hashString2);
        SDL_assert(hashString == hashString3);
    }
}

int main() {
    SDL_LogSetAllPriority(SDL_LOG_PRIORITY_VERBOSE);
    // testArray();
    // testString();
    testHashString();

    return 0;
}