#pragma once

#include "Component.hpp"

#include "physxDefs.hpp"

class Entity;

extern physx::PxPhysics* gPhysics;

class DynamicRigidbodyComponent: public Component {
public: 
    DynamicRigidbodyComponent(Entity &ent, physx::PxScene *scene, const Vector3& linearVelocity, 
        const Vector3& angularVelocity, double mass, double noCollisionTime = 0.);
    ~DynamicRigidbodyComponent();

    void addForceAtCenterOfMass(Vector3 force);

    virtual void update(Entity& ent, double dt) override;

private:
    physx::PxRigidDynamic* dynamicBody = nullptr;
    physx::PxScene *scene = nullptr;

    double activeTime;
    double noCollisionTime;
};