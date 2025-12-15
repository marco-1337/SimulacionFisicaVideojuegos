#include "Entity.hpp"
#include "RenderUtils.hpp"
#include "Component.hpp"

#include <iostream>

using namespace physx;

Entity::Entity(const Vector3& position, const PxGeometry& geometry, Vector4 color)
: myTransform(position){

    myShape = CreateShape(geometry);
    myRenderItem = new RenderItem(myShape, &this->myTransform, color);
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
    return myTransform.p;
}

void
Entity::setPos(Vector3 pos) {
    myTransform.p = pos;
}

void
Entity::translate(Vector3 pos) {
    myTransform.p += pos;
}

void 
Entity::setColor(Vector4 color) {
    myRenderItem->color = color;
}

void 
Entity::addActorToRenderItem(PxRigidActor *actor) {

    RenderItem *aux = myRenderItem;
    myRenderItem = new RenderItem(myShape, actor, aux->color);
    aux->release();
}