#include <Constants.hpp>
#include <Engine.hpp>
#include <ecs/Entity.hpp>
#include <ecs/TransformSystem.hpp>

#include <SDL.h>

#include <Scene.hpp>
#include <container/Array.hpp>
#include <core/String.hpp>
#include <core/StringID.hpp>
#include <math/Matrix4f.hpp>
#include <memory/unique_ptr.hpp>

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
    bool operator==(const TestStruct& other) const { return number == other.number; }

    ~TestStruct() {
        SDL_Log("Destructor");
        number = -1;
    }
};

#include <chrono>

void testArray() {
    edgine::Array<TestStruct> array2;
    array2.create_back().number = 1;

    edgine::Array<TestStruct> array;
    array.create_back().number = 1;
    array.create_back().number = 2;
    array.create_back().number = 3;

    array.erase(array2.find(1));
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

class TestEntity : public edgine::Entity {
public:
    TestEntity(edgine::TransformSystem& transformSystem);

private:
    edgine::TransformComponent mTransformComponent;
};

void testEntityManager() {
    edgine::EntityManager entityManager;

    // edgine::TransformSystem transformSystem;

    // edgine::Entity entity = entityManager.createEntity();
    // edgine::TransformComponent& component = transformSystem.addComponent(entity);
}

void testUniquePtr() {
    edgine::unique_ptr<TestStruct> ptr(new TestStruct(10));

    edgine::unique_ptr<TestStruct> ptr2(std::move(ptr));

    edgine::unique_ptr<TestStruct> ptr3 = std::move(ptr2);

    edgine::unique_ptr<TestStruct> ptr4;
    ptr4.swap(ptr3);

    ptr4.reset(new TestStruct(12));
}

int main(int argc, char* argv[]) {
    (void)argc;
    (void)argv;

    SDL_LogSetAllPriority(SDL_LOG_PRIORITY_VERBOSE);
    testUniquePtr();
    // testString();
    // testStringID();
    // testEntityManager();

    return 0;
}