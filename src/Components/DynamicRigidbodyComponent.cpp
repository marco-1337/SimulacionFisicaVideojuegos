#include "DynamicRigidbodyComponent.hpp"

#include "Entity.hpp"

using namespace physx;

DynamicRigidbodyComponent::DynamicRigidbodyComponent(Entity &ent, PxScene *scene, const Vector3& linearVelocity, 
    const Vector3& angularVelocity, double mass, double noCollisionTime)
: scene(scene),
activeTime(0),
noCollisionTime(noCollisionTime)
{
    dynamicBody = gPhysics->createRigidDynamic(ent.myTransform);
    dynamicBody->attachShape(*(ent.myShape));
    dynamicBody->setLinearVelocity(linearVelocity);
    dynamicBody->setAngularVelocity(angularVelocity);
    dynamicBody->setMaxDepenetrationVelocity(2.0f);
    PxRigidBodyExt::setMassAndUpdateInertia(*dynamicBody, mass);
    scene->addActor(*dynamicBody);

    ent.addActorToRenderItem(dynamicBody);
}

DynamicRigidbodyComponent::~DynamicRigidbodyComponent() {
    scene->removeActor(*dynamicBody);
    dynamicBody->release();
}

void 
DynamicRigidbodyComponent::addForceAtCenterOfMass(Vector3 force) {
    dynamicBody->addForce(force);
}