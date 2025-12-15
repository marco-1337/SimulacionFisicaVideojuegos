#pragma once

#include <PxPhysicsAPI.h>
#include "callbacks.hpp"

extern physx::PxPhysics* gPhysics;

class PhysicsSceneContainer {
public:
    PhysicsSceneContainer();
    ~PhysicsSceneContainer();
protected:
    ContactReportCallback myContactReportCallback;

    physx::PxDefaultCpuDispatcher* myDispatcher = nullptr;
    physx::PxScene* myPhysxScene = nullptr;
};