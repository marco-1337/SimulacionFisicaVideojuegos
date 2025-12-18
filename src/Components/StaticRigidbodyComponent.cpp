#include "StaticRigidbodyComponent.hpp"

#include "Entity.hpp"

using namespace physx;

StaticRigidbodyComponent::StaticRigidbodyComponent(Entity &ent, PxScene *scene) 
: scene(scene) {
    staticBody = gPhysics->createRigidStatic(*(ent.myTransform));

    staticBody->userData = &ent;

    staticBody->attachShape(*(ent.myShape));
    scene->addActor(*staticBody);

    ent.addActorToRenderItem(staticBody);
}

StaticRigidbodyComponent::~StaticRigidbodyComponent() {
    scene->removeActor(*staticBody);
    staticBody->release();
}