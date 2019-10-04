#include "StringID.hpp"

#include <SDL_assert.h>

#ifdef DEBUG
StringID::StringID(Uint32 hashID, const char* const data) : _hashID(hashID), _string(data) {
}
#else
StringID::StringID(Uint32 hashID) : _hashID(hashID) {
}
#endif

bool StringID::operator==(const StringID& rhs) const {
    return _hashID == rhs._hashID;
}

bool StringID::operator!=(const StringID& rhs) const {
    return _hashID != rhs._hashID;
}