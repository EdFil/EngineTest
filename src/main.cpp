#include <Constants.hpp>
#include <Engine.hpp>

#include <SDL.h>

#include <Scene.hpp>
#include <container/Array.hpp>
#include <container/ObjectArray.hpp>
#include <container/ObjectPool.hpp>
#include <container/PODVector.hpp>
#include <core/String.hpp>
#include <core/StringID.hpp>
#include <math/Matrix4f.hpp>

#include <algorithm>
#include <ctime>
#include <iostream>
#include <vector>

struct TestStruct {
    int number;

    TestStruct() : number(0) { SDL_Log("Constructor1"); }
    TestStruct(int number) : number(number) { SDL_Log("Constructor2"); }
    TestStruct(const TestStruct& other) noexcept : number(other.number) {
        SDL_Log("Copy Constructor");
    }
    TestStruct(TestStruct&& other) noexcept : number(std::move(other.number)) {
        SDL_Log("Move Constructor");
    }
    TestStruct& operator=(const TestStruct& rhs) {
        SDL_Log("Copy Operator");
        number = rhs.number;
        return *this;
    }
    TestStruct& operator=(TestStruct&& rhs) noexcept {
        SDL_Log("Move Operator");
        number = rhs.number;
        return *this;
    }
    ~TestStruct() { SDL_Log("Destructor"); }
};

#include <chrono>

void testObjectArray() {
    ObjectArray<String> testArray;
    testArray.push_back({"This is a string 1"});
    testArray.push_back({"This is a string 2"});
    testArray.push_back({"This is a string 3"});
    testArray.push_back({"This is a string 4"});
    testArray.push_back({"This is a string 5"});
    testArray.push_back({"This is a string 6"});
    testArray.push_back({"This is a string 7"});
    testArray.push_back({"This is a string 8"});
    testArray.resize(4);

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

void testArray() {
    Array<TestStruct> array;
    array.create_back();
    array.create_back();
    array.create_back();
    array.create_back();
    array.create_back();
    array.create_back();

	array.reserve(2);
    array.resize(2);
    array.resize(20);
 
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

void testEntityManager() {
    EntityManager manager;
    manager.initWithCapacity(4);

	Entity entity1_0 = manager.createEntity();
    Entity entity2_0 = manager.createEntity();
    manager.destroyEntity(entity1_0);

    Entity entity1_1 = manager.createEntity();
    Entity entity3_0 = manager.createEntity();
    Entity entity4_0 = manager.createEntity();
    Entity entity5_0 = manager.createEntity();

	manager.destroyEntity(entity1_0);
}

int main(int argc, char* argv[]) {
    (void)argc;
    (void)argv;

    SDL_LogSetAllPriority(SDL_LOG_PRIORITY_VERBOSE);
    testArray();
    testObjectArray();
    // testString();
    // testStringID();
    // testObjectPool();
    testEntityManager();

    return 0;
}