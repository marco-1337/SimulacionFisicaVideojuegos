#include "DynamicRigidbodyComponent.hpp"

#include "Entity.hpp"

using namespace physx;

DynamicRigidbodyComponent::DynamicRigidbodyComponent(Entity &ent, PxScene *scene, const Vector3& linearVelocity, 
    const Vector3& angularVelocity, double mass, double noCollisionTime = 0.)
: scene(scene),
activeTime(0),
noCollisionTime((noCollisionTime))
{
    dynamicBody = gPhysics->createRigidDynamic(ent.myTransform);
    dynamicBody->attachShape(*(ent.myShape));
    dynamicBody->setLinearVelocity(linearVelocity);
    dynamicBody->setAngularVelocity(angularVelocity);
    PxRigidBodyExt::setMassAndUpdateInertia(*dynamicBody, mass);
    scene->addActor(*dynamicBody);

    ent.addActorToRenderItem(dynamicBody);

    if (noCollisionTime > 0.) {
            ent.myShape->setFlag(PxShapeFlag::eSIMULATION_SHAPE, true);
    }
}

DynamicRigidbodyComponent::~DynamicRigidbodyComponent() {
    scene->removeActor(*dynamicBody);
    dynamicBody->release();
}

void 
DynamicRigidbodyComponent::addForceAtCenterOfMass(Vector3 force) {
    dynamicBody->addForce(force);
}

void
DynamicRigidbodyComponent::update(Entity& ent, double dt) {
    if (activeTime <= noCollisionTime) {
        activeTime += dt;

        if (activeTime >= noCollisionTime) {
            ent.myShape->setFlag(PxShapeFlag::eSIMULATION_SHAPE, true);
        }
    }
}