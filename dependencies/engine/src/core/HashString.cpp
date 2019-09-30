#include "HashString.hpp"

#include <SDL_assert.h>

// From: http://www.cse.yorku.ca/~oz/hash.html

#ifdef DEBUG
HashString::HashString(Uint32 hashID, const char* const data) : _hashID(hashID), _string(data) {
}
#else
HashString::HashString(Uint32 hashID) : _hashID(hashID) {
}
#endif

bool HashString::operator==(const HashString& rhs) const {
    return _hashID == rhs._hashID;
}

bool HashString::operator!=(const HashString& rhs) const {
    return _hashID != rhs._hashID;
}