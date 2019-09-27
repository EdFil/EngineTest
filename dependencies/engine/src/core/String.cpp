#include "core/String.hpp"

#include <SDL_log.h>

namespace string_internal {
    char kEmptyString[] = "";
}

String::String() : _data(string_internal::kEmptyString) {}
String::String(const char* data) { init(data); }
String::String(const String& other) { init(other._data, other._length); }

String::String(String&& other) noexcept {
    SDL_memcpy(this, &other, sizeof(String));
    SDL_memset(&other, 0, sizeof(String));
}

String::~String() {
    if (_capacity > 0) {
        SDL_free(_data);
    }
}

String& String::operator=(const char* rhs) {
    init(rhs);
    return *this;
}

String& String::operator=(const String& rhs) {
    init(rhs._data, rhs._length);
    return *this;
}

String& String::operator=(String&& rhs) noexcept {
    SDL_memcpy(this, &rhs, sizeof(String));
    SDL_memset(&rhs, 0, sizeof(String));
    return *this;
}

bool String::init(const char* const data) {
    if (data == nullptr) {
        _data = string_internal::kEmptyString;
        _length = 0;
        return false;
    } else {
        Uint32 length = SDL_strlen(data);
        return init(data, length);
    }
}

bool String::init(const char* const data, Uint32 length) {
    const Uint32 newDataSize = sizeof(char) * (length + 1);

    // If we need to allocate memory
    if (length > _capacity) {
        // Allocate
        char* newData = static_cast<char*>(SDL_malloc(sizeof(char) * length));
        if (newData == nullptr) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[String::init] Error on malloc(%d)",
                         newDataSize);
            return false;
        }
        SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "[String::init] Allocate %d bytes", newDataSize);

        // Copy
        if (!SDL_memcpy(newData, data, newDataSize)) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[String::init] Error on memcpy(%p, %p, %d)",
                         (void*)newData, (void*)data, newDataSize);
            SDL_free(newData);
            return false;
        }

        // Cleanup old
        if (_capacity != 0) {
            SDL_free(_data);
        }

        _data = newData;
        _length = _capacity = length;
    } else {
        // Copy
        if (!SDL_memcpy(_data, data, newDataSize)) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[String::init] Error on memcpy(%p, %p, %d)",
                         (void*)_data, (void*)data, newDataSize);
            return false;
        }

        _length = length;
    }

    return true;
}