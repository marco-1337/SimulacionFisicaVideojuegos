#include "DynamicRigidbodyComponent.hpp"

#include "Entity.hpp"

using namespace physx;

DynamicRigidbodyComponent::DynamicRigidbodyComponent(Entity &ent, PxScene *scene, const Vector3& linearVelocity, 
    const Vector3& angularVelocity, double mass, physx::PxReal staticFrition, physx::PxReal dynamicFrition,
    physx::PxReal restitution, float linearDamping, float angularDamping )
: scene(scene),
activeTime(0) {

    dynamicBody = gPhysics->createRigidDynamic(*(ent.myTransform));

    PxMaterial *mat;
    ent.myShape->getMaterials(&mat, 1);
    
    mat->setStaticFriction(staticFrition);
    mat->setDynamicFriction(dynamicFrition);
    mat->setRestitution(restitution);
    
    dynamicBody->setLinearDamping(linearDamping);
    dynamicBody->setAngularDamping(angularDamping);

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