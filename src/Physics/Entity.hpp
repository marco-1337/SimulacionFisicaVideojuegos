#pragma once

#include <PxPhysicsAPI.h>

class RenderItem;

using Vector3 = physx::PxVec3;
using Vector4 = physx::PxVec4;
using Shape = physx::PxShape;

static constexpr double PI = 3.14159265358979323846;

static constexpr double GRAVITY = -9.8;

class Entity {
public:
    Entity(Vector3 position, Shape *shape, Vector4 color);
    virtual ~Entity();

    virtual void enableRender();
    inline virtual void update(double t) {}
    // Esto es ser perezoso pero bueno, es lo que hay
    inline virtual void addForce(Vector3 f) {}
    inline virtual double getMass() const { return 0.; }
    
    inline bool isAlive() const { return alive; }
    
    inline void kill() { alive = false; }



protected:

    bool alive = true;

    RenderItem* myRenderItem;
    physx::PxTransform myTransform;
};