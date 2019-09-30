#include <SDL_stdinc.h>

class String {
public:
    String();
    String(const char* const data);
    String(const String& string);
    String(String&& string) noexcept;
    ~String();

    bool isEmpty() const { return _length == 0; }
    char* data() const { return _data; }
    Uint32 length() const { return _length; }
    Uint32 capacity() const { return _capacity; }

    bool operator==(const char* const rhs) const;
    bool operator==(const String& rhs) const;

    String& operator=(const char* const rhs);
    String& operator=(const String& rhs);
    String& operator=(String&& rhs) noexcept;

private:
    char* _data = nullptr;
    Uint32 _length = 0;
    Uint32 _capacity = 0;

    bool init(const char* const data);
    bool init(const char* const data, Uint32 length);
};