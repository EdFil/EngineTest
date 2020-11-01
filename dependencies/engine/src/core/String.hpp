#pragma once

#include <cstdint>

class String {
public:
    String();
    String(const char* const data);
    String(const String& string);
    String(String&& string) noexcept;
    ~String();

    bool isEmpty() const { return m_length == 0; }
    const char* data() const { return m_pData; }
    uint32_t length() const { return m_length; }
    uint32_t capacity() const { return m_capacity; }

    bool operator==(const char* const rhs) const;
    bool operator==(const String& rhs) const;

    String& operator=(const char* const rhs);
    String& operator=(const String& rhs);
    String& operator=(String&& rhs) noexcept;

private:
    char* m_pData = nullptr;
    uint32_t m_length = 0;
    uint32_t m_capacity = 0;

    bool init(const char* const data);
    bool init(const char* const data, uint32_t length);
};