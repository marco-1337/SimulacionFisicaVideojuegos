#include "StaticRigidbodyComponent.hpp"

#include "Entity.hpp"

using namespace physx;

StaticRigidbodyComponent::StaticRigidbodyComponent(Entity &e, PxScene *scene) 
: scene(scene) {
    staticBody = gPhysics->createRigidStatic(*(e.myTransform));
    staticBody->attachShape(*(e.myShape));
    scene->addActor(*staticBody);

    e.addActorToRenderItem(staticBody);
}

StaticRigidbodyComponent::~StaticRigidbodyComponent() {
    scene->removeActor(*staticBody);
    staticBody->release();
}