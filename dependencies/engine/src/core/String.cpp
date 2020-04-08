#include "core/String.hpp"

#include <SDL_log.h>

namespace string_internal {
    char kEmptyString[] = "";
}

String::String() : m_pData(string_internal::kEmptyString) {
}

String::String(const char* data) {
    init(data);
}

String::String(const String& other) {
    init(other.m_pData, other.m_length);
}

String::String(String&& other) noexcept {
    m_pData = other.m_pData;
    m_capacity = other.m_capacity;
    m_length = other.m_length;
    
    SDL_memset(&other, 0, sizeof(String));
}

String::~String() {
    if (m_capacity > 0) {
        SDL_free(m_pData);
    }
}

bool String::operator==(const char* rhs) const {
    if (rhs == nullptr) {
        return false;
    }

    return SDL_strcmp(m_pData, rhs) == 0;
}

bool String::operator==(const String& rhs) const {
    return SDL_strcmp(m_pData, rhs.m_pData) == 0;
}

String& String::operator=(const char* rhs) {
    init(rhs);
    return *this;
}

String& String::operator=(const String& rhs) {
    init(rhs.m_pData, rhs.m_length);
    return *this;
}

String& String::operator=(String&& rhs) noexcept {
    SDL_memcpy(this, &rhs, sizeof(String));
    SDL_memset(&rhs, 0, sizeof(String));
    return *this;
}

bool String::init(const char* const data) {
    if (data == nullptr || data[0] == '\0') {
        m_pData = string_internal::kEmptyString;
        m_length = 0;
        return false;
    } else {
        Uint32 length = (Uint32)SDL_strlen(data);
        return init(data, length);
    }
}

bool String::init(const char* const data, Uint32 length) {
    const Uint32 newDataSize = (Uint32)sizeof(char) * (length + 1);

    // If we need to allocate memory
    if (length > m_capacity) {
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
        if (m_capacity != 0) {
            SDL_free(m_pData);
        }

        m_pData = newData;
        m_length = m_capacity = length;
    } else {
        // Copy
        if (!SDL_memcpy(m_pData, data, newDataSize)) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                         "[String::init] (%p) Error on memcpy(%p, %p, %d)", (void*)this,
                         (void*)m_pData, (void*)data, newDataSize);
            return false;
        }

        m_length = length;
    }

    return true;
}