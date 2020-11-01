#include <cstdint>

#ifdef DEBUG
#include "String.hpp"
#endif

constexpr const int8_t STRING_END_BYTE = 0;
constexpr const uint32_t STRING_BIT_SHIT = 5;
constexpr const uint32_t STRING_HASH_KEY = 5381;

constexpr uint32_t some_hash_function(const char* pTail, uint32_t hash = STRING_HASH_KEY) {
    while (*pTail != STRING_END_BYTE) {
        hash = (hash << STRING_BIT_SHIT) + hash + (int32_t)*pTail;
        pTail++;
    }
    return hash;
}

template <uint32_t hash>
inline constexpr uint32_t compile_time_hash() {
    return hash;
}

#if COMPILE_TIME_STRING_ID == 1
#define HASH(__STRING__) compile_time_hash<some_hash_function(__STRING__)>()
#else
#define HASH(__STRING__) some_hash_function(__STRING__)
#endif

#ifdef DEBUG
#define SID(__STRING__) StringID(HASH(__STRING__), __STRING__)
#else
#define SID(__STRING__) StringID(HASh(__STRING__))
#endif

class StringID {
public:
#ifdef DEBUG
    StringID(uint32_t hashID, const char* const data);
#else
    StringID(uint32_t hashID);
#endif

    uint32_t id() const { return _hashID; }
#ifdef DEBUG
    const char* data() const { return _string.data(); }
#endif

    bool operator==(const StringID& rhs) const;
    bool operator!=(const StringID& rhs) const;

private:
    uint32_t _hashID;
#ifdef DEBUG
    String _string;
#endif
};