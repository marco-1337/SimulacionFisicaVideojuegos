#pragma once

#include "Component.hpp"

#include "physxDefs.hpp"

class Entity;

extern physx::PxPhysics* gPhysics;

class DynamicRigidbodyComponent: public Component {
public:
    DynamicRigidbodyComponent(Entity &ent, physx::PxScene *scene, const Vector3& linearVelocity, 
        const Vector3& angularVelocity, double mass, float staticFrition = 0.5f, float dynamicFrition = 0.5f,
        float restitution = 0.5f, float linearDamping = 0.f, float angularDamping = 0.f);
    ~DynamicRigidbodyComponent();
    
    void addForceAtCenterOfMass(Vector3 force);

private:
    physx::PxRigidDynamic* dynamicBody = nullptr;
    physx::PxScene *scene = nullptr;

    double activeTime;
    double noCollisionTime;
};