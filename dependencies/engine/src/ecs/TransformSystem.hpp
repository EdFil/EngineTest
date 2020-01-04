#pragma once

#include "math/Vector3f.hpp"
#include "container/Array.hpp"

#include "ecs/EntityManager.hpp"

#include <multi>

//  Depth
//   [1] --> [A, B, C]
//   [2] --> [A, B, B, B, C, C] 
//   [3] --> [A, C, C, C]

//   [            A             ]
//   [A,    B,    C,      D     ]
//   [A] [A B C] [] [A, B, C, D]


struct TransformComponent {
    Vector3f m_localPosition;
    Vector3f m_worldPosition;
    Vector3f m_rotation;
};

struct SceneGraphComponent {
    TransformComponent* parent;
    Array<SceneGraphComponent> m_children;
};

class TransformSystem {
    TransformSystem() = default;
    TransformSystem(const TransformSystem& rhs) = delete;
    TransformSystem(const TransformSystem&& rhs) = delete;
    TransformSystem& operator=(const TransformSystem& rhs) = delete;
    TransformSystem& operator=(const TransformSystem&& rhs) = delete;

	TransformComponent getComponent(const Entity& entity);

	<Entity, TransformComponent>
};