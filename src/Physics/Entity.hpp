#pragma once

#include <PxPhysicsAPI.h>

class RenderItem;

using Vector3 = physx::PxVec3;
using Vector4 = physx::PxVec4;
using Shape = physx::PxShape;

class Entity {
public:
    Entity(Vector3 position, Shape *shape, Vector4 color);
    virtual ~Entity() = 0;
    virtual void enableRender();
    virtual void update(double t) = 0;
    virtual bool needToDelete() = 0;
protected:
    RenderItem* myRenderItem;
    physx::PxTransform myTransform;
};