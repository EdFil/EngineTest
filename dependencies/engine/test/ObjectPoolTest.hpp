#pragma once

#include "gtest/gtest.h"

#include "../src/container/ObjectPool.hpp"

namespace {

    class ObjectPoolTest : public ::testing::Test {
    protected:
        // You can remove any or all of the following functions if its body
        // is empty.

        ObjectPoolTest() {
            // You can do set-up work for each test here.
        }

        ~ObjectPoolTest() override {
            // You can do clean-up work that doesn't throw exceptions here.
        }

        // If the constructor and destructor are not enough for setting up
        // and cleaning up each test, you can define the following methods:

        void SetUp() override {
            // Code here will be called immediately after the constructor (right
            // before each test).
        }

        void TearDown() override {
            // Code here will be called immediately after each test (right
            // before the destructor).
        }

        // Objects declared here can be used by all tests in the test case for Foo.
    };

    TEST_F(ObjectPoolTest, GetAnElement) {
        ObjectPool<int> pool;
        pool.initWithSize(1);

        ObjectPoolHandle handle = pool.getNewHandle();
        EXPECT_TRUE(handle != k_invalidHandle);

        int& pooledObject = pool[handle];
        pooledObject = 102;
    }

    TEST_F(ObjectPoolTest, PoolIsFull) {
        const unsigned numElems = 5;
        ObjectPool<int> pool;
        pool.initWithSize(numElems);
        ObjectPoolHandle handles[numElems];
        for (unsigned i = 0; i < numElems; i++) {
            handles[i] = pool.getNewHandle();
        }

        EXPECT_EQ(pool.getNewHandle(), UINT32_MAX);
    }

}