#include "PhysicsSceneContainer.hpp"

using namespace physx;

PhysicsSceneContainer::PhysicsSceneContainer() {
    PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.81f, 0.0f);
	myDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = myDispatcher;
	sceneDesc.filterShader = contactReportFilterShader;
	sceneDesc.simulationEventCallback = &myContactReportCallback;
	myPhysxScene = gPhysics->createScene(sceneDesc);
}

PhysicsSceneContainer::~PhysicsSceneContainer() {
    myPhysxScene->release();
	myDispatcher->release();
}