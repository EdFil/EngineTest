#pragma once

#include <vector>

#include "ECS.h"

class Entity {
    void addComponenthandle(GlobalHandle globalHandle);
    void removeComponentHandle(GlobalHandle globalHandle);

private:
    std::vector<GlobalHandle> _componentHandles;
};

