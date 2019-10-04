#include "core/String.hpp"

#include <SDL_log.h>

namespace string_internal {
    char kEmptyString[] = "";
}

String::String() : _data(string_internal::kEmptyString) {
}

String::String(const char* data) {
    init(data);
}

String::String(const String& other) {
    init(other._data, other._length);
}

String::String(String&& other) noexcept {
    SDL_memcpy(this, &other, sizeof(String));
    SDL_memset(&other, 0, sizeof(String));
}

String::~String() {
    if (_capacity > 0) {
        SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "[String::init] (%p) Delete %lu bytes",
                     (void*)this, (_capacity + 1) * sizeof(char));
        SDL_free(_data);
    }
}

bool String::operator==(const char* rhs) const {
    if (rhs == nullptr) {
        return false;
    }

    return SDL_strcmp(_data, rhs) == 0;
}

bool String::operator==(const String& rhs) const {
    return SDL_strcmp(_data, rhs._data) == 0;
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
    if (data == nullptr || data[0] == '\0') {
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
        char* newData = static_cast<char*>(SDL_malloc(newDataSize));
        if (newData == nullptr) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[String::init] (%p) Error on malloc(%d)",
                         (void*)this, newDataSize);
            return false;
        }
        SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "[String::init] (%p) Allocate %d bytes",
                     (void*)this, newDataSize);

        // Copy
        if (!SDL_memcpy(newData, data, newDataSize)) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                         "[String::init] (%p) Error on memcpy(%p, %p, %d)", (void*)this,
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
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                         "[String::init] (%p) Error on memcpy(%p, %p, %d)", (void*)this,
                         (void*)_data, (void*)data, newDataSize);
            return false;
        }

        _length = length;
    }

    return true;
}