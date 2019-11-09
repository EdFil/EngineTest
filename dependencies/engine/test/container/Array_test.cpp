#include <gtest/gtest.h>

#include <container/Array.hpp>

namespace {

    struct ArrayTestObjectCounter {
        int m_numConstructorCalls;
        int m_numMoveCalls;
        int m_numCopyCalls;
        int m_numDestructorCalls;

        void EXPECT(const ArrayTestObjectCounter& other) {
            EXPECT_EQ(m_numConstructorCalls, other.m_numConstructorCalls);
            EXPECT_EQ(m_numMoveCalls, other.m_numMoveCalls);
            EXPECT_EQ(m_numCopyCalls, other.m_numCopyCalls);
            EXPECT_EQ(m_numDestructorCalls, other.m_numDestructorCalls);
        }
    };

    static ArrayTestObjectCounter s_counter = {0, 0, 0, 0};

    struct ArrayTestObject {
        ArrayTestObject() { s_counter.m_numConstructorCalls++; }
        ArrayTestObject(const ArrayTestObject&) { s_counter.m_numCopyCalls++; }
        ArrayTestObject(ArrayTestObject&&) noexcept { s_counter.m_numMoveCalls++; }
        ArrayTestObject& operator=(const ArrayTestObject&) {
            s_counter.m_numCopyCalls++;
            return *this;
        }
        ArrayTestObject& operator=(ArrayTestObject&&) noexcept {
            s_counter.m_numMoveCalls++;
            return *this;
        }
        ~ArrayTestObject() { s_counter.m_numDestructorCalls++; }
    };

    TEST(Array, DefaultContructor) {
        Array<ArrayTestObject> array;
        EXPECT_EQ(SDL_GetNumAllocations(), 0);
        EXPECT_EQ(array.size(), 0u);
        EXPECT_TRUE(array.isEmpty());
    }

    TEST(Array, SizeConstructorData) {
        Array<ArrayTestObject, false> array(10);
        EXPECT_EQ(SDL_GetNumAllocations(), 1);
        EXPECT_EQ(array.size(), 10u);
        EXPECT_FALSE(array.isEmpty());
    }

    TEST(Array, SizeConstructorObject) {
        s_counter = {0, 0, 0, 0};
        {
            Array<ArrayTestObject, true> array(10);
            s_counter.EXPECT({10, 0, 0, 0});
            EXPECT_EQ(array.size(), 10u);
            EXPECT_FALSE(array.isEmpty());
        }
        s_counter.EXPECT({10, 0, 0, 10});
        EXPECT_EQ(SDL_GetNumAllocations(), 0);
    }

    TEST(Array, ResizeUp) {
        s_counter = {0, 0, 0, 0};
        {
            Array<ArrayTestObject, true> array(5);
            array.resize(10);
            s_counter.EXPECT({10, 5, 0, 0});
            EXPECT_EQ(array.size(), 10u);
            EXPECT_FALSE(array.isEmpty());
        }
        s_counter.EXPECT({10, 5, 0, 10});
        EXPECT_EQ(SDL_GetNumAllocations(), 0);
    }

    TEST(Array, ResizeDown) {
        s_counter = {0, 0, 0, 0};
        {
            Array<ArrayTestObject, true> array(10);
            array.resize(5);
            s_counter.EXPECT({10, 5, 0, 5});
            EXPECT_EQ(array.size(), 5u);
            EXPECT_FALSE(array.isEmpty());
        }
        s_counter.EXPECT({10, 5, 0, 10});
        EXPECT_EQ(SDL_GetNumAllocations(), 0);
    }
}  // namespace