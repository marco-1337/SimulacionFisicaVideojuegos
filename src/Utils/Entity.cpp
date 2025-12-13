#include "Entity.hpp"
#include "RenderUtils.hpp"
#include "Component.hpp"

using namespace physx;

Entity::Entity(Vector3 position, Shape *shape, Vector4 color)
: myTransform(position) {
    myRenderItem = new RenderItem(shape, &this->myTransform, color);
}

Entity::~Entity() {
    if (myRenderItem) myRenderItem->release();
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