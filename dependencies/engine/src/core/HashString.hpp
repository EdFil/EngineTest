#include <SDL_stdinc.h>

#ifdef DEBUG
#include "String.hpp"
#endif

constexpr Uint32 hash(char const* str) {
    Uint32 hash = 5381;
    int c = 0;

    while ((c = *str++) != 0) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }

    return hash;
}

#ifdef DEBUG
#define CreateHashString(__STRING__) HashString(hash(__STRING__), __STRING__)
#else
#define CreateHashString(__STRING__) HashString(hash(__STRING__))
#endif

class HashString {
public:
#ifdef DEBUG
    HashString(Uint32 hashID, const char* const data);
#else
    HashString(Uint32 hashID);
#endif

    Uint32 id() const { return _hashID; }
#ifdef DEBUG
    const char* data() const { return _string.data(); }
#endif

    bool operator==(const HashString& rhs) const;
    bool operator!=(const HashString& rhs) const;

private:
    Uint32 _hashID;
#ifdef DEBUG
    String _string;
#endif
};