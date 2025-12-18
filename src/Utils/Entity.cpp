#include "Entity.hpp"
#include "RenderUtils.hpp"
#include "Component.hpp"

#include <iostream>

using namespace physx;

Entity::Entity(const Vector3& position, const PxGeometry& geometry, Vector4 color)
: myTransform(new physx::PxTransform(position)){

    myShape = CreateShape(geometry);
    myRenderItem = new RenderItem(myShape, this->myTransform, color);
}

Entity::~Entity() {
    if (myRenderItem) myRenderItem->release();
    if (myShape) myShape->release();
}


void
Entity::update(double t) {

    for (int i = 0; i < maxComponentId; ++i) {
        if (components[i] != nullptr) {
            components[i]->update(*this, t);
        }
    }
}

void 
Entity::enableRender() {
    if (myRenderItem != nullptr) RegisterRenderItem(myRenderItem);
}

Vector3
Entity::getPos() const{
    if (myTransform) {
        return myTransform->p;
    }
    else if (myActor) {
        return myActor->getGlobalPose().p;
    }

    return Vector3(0.);
}

void
Entity::setPos(Vector3 pos) {
    if (myTransform) {
        myTransform->p = pos;
    }
}

void
Entity::translate(Vector3 pos) {
    if (myTransform) {
        myTransform->p += pos;
    }
}

double
Entity::getBoundsHeight() {

    PxGeometryHolder geometry = myShape->getGeometry();

    PxBounds3 bounds = PxGeometryQuery::getWorldBounds(
        geometry.any(),
        ((myActor != nullptr) ? myActor->getGlobalPose() : PxTransform(PxIdentity))
    );

    return (bounds.maximum.y - bounds.minimum.y);
}

double
Entity::getApproximatedVolume() {

    if (myActor) {
        
        PxShape* shape = nullptr;
        myActor->getShapes(&shape, 1);

        PxBounds3 bounds = PxShapeExt::getWorldBounds(*shape, *myActor);
        Vector3 size = bounds.maximum - bounds.minimum;

        return size.x * size.y * size.z;
    }
    else {
        return 1.;
    }
}

void 
Entity::setColor(Vector4 color) {
    myRenderItem->color = color;
}

void 
Entity::addActorToRenderItem(PxRigidActor *actor) {

    RenderItem *aux = myRenderItem;

    myRenderItem = new RenderItem(myShape, actor, aux->color);
    myActor = actor;

    aux->release();

    delete myTransform;
    myTransform = nullptr;
}