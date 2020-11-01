#include "StringID.hpp"

#ifdef DEBUG
StringID::StringID(uint32_t hashID, const char* const data) : _hashID(hashID), _string(data) {
}
#else
StringID::StringID(uint32_t hashID) : _hashID(hashID) {
}
#endif

bool StringID::operator==(const StringID& rhs) const {
    return _hashID == rhs._hashID;
}

bool StringID::operator!=(const StringID& rhs) const {
    return _hashID != rhs._hashID;
}