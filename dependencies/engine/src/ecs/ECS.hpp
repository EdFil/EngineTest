#pragma once

#include <cstdint>

enum class ComponentStatus : int8_t {
	Free = 0, Used = 1
};

constexpr uint32_t generateContiguousBitMask(uint8_t start, uint8_t length) {
    uint32_t mask = 0xFFFFFFFF;
    mask >>= 32 - length;
    mask <<= start;
    return mask;
}

// GlobalHandle breakdown
//
//   0000 0000 0000 0000 0000 0000 0000 0000
//   |       | |         LocalIndex        |
//       ^                   ^
//  SystemIndex          LocalIndex
//  2^8 Systems        2^24 Components

static const uint8_t k_numBitsIndex = 8;
static const uint32_t k_systemIndex = generateContiguousBitMask(32, k_numBitsIndex);
static const uint32_t k_localIndex  = ~k_systemIndex;

using GlobalHandle = uint32_t;
using SystemIndex = GlobalHandle;
using LocalIndex = GlobalHandle;