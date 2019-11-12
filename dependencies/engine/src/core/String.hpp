#pragma once

#include <SDL_stdinc.h>

class String {
public:
    String();
    String(const char* const data);
    String(const String& string);
    String(String&& string) noexcept;
    ~String();

    bool isEmpty() const { return m_length == 0; }
    const char* data() const { return m_pData; }
    Uint32 length() const { return m_length; }
    Uint32 capacity() const { return m_capacity; }

    bool operator==(const char* const rhs) const;
    bool operator==(const String& rhs) const;

    String& operator=(const char* const rhs);
    String& operator=(const String& rhs);
    String& operator=(String&& rhs) noexcept;

private:
    char* m_pData = nullptr;
    Uint32 m_length = 0;
    Uint32 m_capacity = 0;

    bool init(const char* const data);
    bool init(const char* const data, Uint32 length);
};