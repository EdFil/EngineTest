#include <cstdint>
#include <string>

using ResourceHandle = uint32_t;

class Resource {
public:
    enum class Type { Undefined = 0, Shader, Texture };

    enum class State {
        Unloaded = 0,
        Loading,
        Loaded
    }

    Resource(Type type, const std::string& name);
    virtual ~Resource();

    virtual void load();
    virtual void unload();
    virtual void incRef();
    virtual void decRef();

protected:
    Type _type;
    State _state;
    uint32_t _refCount;
    std::string _name;
};

#include <map>

class ResourceManager {
public:
    ResourcrManager();

private:
    std::vector<Resource*> _resources;
}