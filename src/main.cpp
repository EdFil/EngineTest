#include <Constants.hpp>
#include <Engine.hpp>

#include <SDL.h>

#include <Scene.hpp>
#include <container/Array.hpp>
#include <container/ObjectPool.hpp>
#include <container/PODVector.hpp>
#include <core/String.hpp>
#include <core/StringID.hpp>
#include <math/Matrix4f.hpp>

#include <algorithm>
#include <ctime>
#include <iostream>
#include <vector>

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

struct TestStruct {
    float health;
    int number;

    TestStruct() : health(0.0f), number(0) { SDL_Log("Constructor1"); }
    TestStruct(float health, int number) : health(health), number(number) {
        SDL_Log("Constructor2");
    }
    TestStruct(const TestStruct&) noexcept { SDL_Log("Copy Constructor"); }
    TestStruct(TestStruct&&) noexcept { SDL_Log("Move Constructor"); }
    TestStruct& operator=(const TestStruct&) {
        SDL_Log("Copy Operator");
        return *this;
    }
    TestStruct& operator=(TestStruct&&) noexcept {
        SDL_Log("Move Operator");
        return *this;
    }
    ~TestStruct() { SDL_Log("Destructor"); }
};

#include <chrono>

void testArray() {
    Array<TestStruct, false> testArray;
    printf("resize 2\n");
    testArray.resize(2);
    printf("resize 4\n");
    testArray.resize(4);
    printf("resize 2\n");
    testArray.resize(2);
    printf("end\n");

    // const unsigned kInitialSize = 1000;
    // const unsigned kNumElems = 1000;
    // {
    //     auto timepoint = std::chrono::high_resolution_clock::now();
    //     PODArray<TestStruct> testArray(kInitialSize);
    //     for (unsigned i = 0; i < kNumElems; i++) {
    //         testArray[i] = {1.0f, (int)i};
    //     }
    //     SDL_Log("Took %lld", (long long)std::chrono::duration_cast<std::chrono::nanoseconds>(
    //                              std::chrono::high_resolution_clock::now() - timepoint)
    //                              .count());
    // }

    // {
    //     auto timepoint = std::chrono::high_resolution_clock::now();
    //     PODArray<TestStruct> testArray(kInitialSize);
    //     for (unsigned i = 0; i < kNumElems; i++) {
    //         testArray[i].health = 1.0f;
    //         testArray[i].health = i;
    //     }
    //     SDL_Log("Took %lld", (long long)std::chrono::duration_cast<std::chrono::nanoseconds>(
    //                              std::chrono::high_resolution_clock::now() - timepoint)
    //                              .count());

    //     for (auto& elem : testArray) {
    //         (void)elem;
    //     }
    // }
}

void testVector() {
    {
        auto timepoint = std::chrono::high_resolution_clock::now();
        std::vector<int> coisa;
        coisa.push_back(1);
        coisa.push_back(2);
        coisa.push_back(3);
        coisa.push_back(4);
        coisa.push_back(5);

        coisa.erase(std::find(coisa.cbegin(), coisa.cend(), 3));
        SDL_Log("std::vector Took %lld",
                (long long)std::chrono::duration_cast<std::chrono::nanoseconds>(
                    std::chrono::high_resolution_clock::now() - timepoint)
                    .count());
    }

    {
        auto timepoint = std::chrono::high_resolution_clock::now();
        PODVector<int> vector;
        vector.push_back(1);
        vector.push_back(2);
        vector.push_back(3);
        vector.push_back(4);
        vector.push_back(5);

        vector.erase(3);
        SDL_Log("PODVector Took %lld",
                (long long)std::chrono::duration_cast<std::chrono::nanoseconds>(
                    std::chrono::high_resolution_clock::now() - timepoint)
                    .count());
    }

    {
        auto timepoint = std::chrono::high_resolution_clock::now();
        PODVector<int> vector2;
        vector2.push_back(1);
        vector2.push_back(2);
        vector2.push_back(3);
        vector2.push_back(4);
        vector2.push_back(5);

        vector2.fast_erase(3);
        SDL_Log("PODVector fast Took %lld",
                (long long)std::chrono::duration_cast<std::chrono::nanoseconds>(
                    std::chrono::high_resolution_clock::now() - timepoint)
                    .count());
    }

    SDL_Log("End");
}

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

void testStringID() {
    {
        StringID test1 = SID("String 1");
        StringID test2 = SID("String 2");
        StringID test3 = SID("String 1");
        StringID test4 = test1;
        StringID test5 = SID(" ");

        SDL_assert(test1 != test2);
        SDL_assert(test1 == test3);
        SDL_assert(test3 == test4);
    }
}

struct TestClass {
    int i;
};

void testObjectPool() {
    //   ObjectPool<TestClass> objectPool1;
    //   ObjectPoolHandle handle0 = objectPool1.getNewHandle();
    //   objectPool1[handle0].i = 9;
    //   ObjectPoolHandle handle1 = objectPool1.getNewHandle();
    //   objectPool1[handle1].i = 98;
    //   ObjectPoolHandle handle2 = objectPool1.getNewHandle();
    //   objectPool1[handle2].i = 987;
    //   ObjectPoolHandle handle3 = objectPool1.getNewHandle();
    //   objectPool1[handle3].i = 9876;
    //
    // objectPool1.releaseHandle(handle0);
    //   objectPool1.releaseHandle(handle2);
    //   objectPool1.releaseHandle(handle1);
    //   objectPool1.releaseHandle(handle3);
    //   objectPool1.releaseHandle(handle3);

    // handle3 = objectPool1.getNewHandle();
    //   objectPool1[handle3].i = 0;
    //   handle1 = objectPool1.getNewHandle();
    //   objectPool1[handle1].i = 0;
    //   handle2 = objectPool1.getNewHandle();
    //   objectPool1[handle2].i = 0;
    //   handle0 = objectPool1.getNewHandle();
    //   objectPool1[handle0].i = 0;
}

int main(int argc, char* argv[]) {
    (void)argc;
    (void)argv;

    SDL_LogSetAllPriority(SDL_LOG_PRIORITY_VERBOSE);
    testArray();
    // testVector();
    // testString();
    // testStringID();
    // testObjectPool();

    return 0;
}