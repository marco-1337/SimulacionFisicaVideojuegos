#pragma once

#include "Component.hpp"

#include "physxDefs.hpp"

class Entity;

extern physx::PxPhysics* gPhysics;

class StaticRigidbodyComponent: public Component {
public: 
    StaticRigidbodyComponent(Entity &e, physx::PxScene *scene);
    ~StaticRigidbodyComponent();
private:
    physx::PxRigidStatic* staticBody = nullptr;
    physx::PxScene *scene = nullptr;
};