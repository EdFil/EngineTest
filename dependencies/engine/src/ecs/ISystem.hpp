#pragma once

namespace edgine {

    class ISystem {
    public:
        virtual ~ISystem() = default;

        virtual void update(float delta) = 0;
    };

}  // namespace edgine