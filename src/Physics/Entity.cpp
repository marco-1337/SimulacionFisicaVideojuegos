#include "Entity.hpp"
#include "RenderUtils.hpp"

using namespace physx;

const Vector3 GRAVITY = Vector3(0., -9.8, 0.);

Entity::Entity(Vector3 position, Shape *shape, Vector4 color) {
    this->myTransform = PxTransform(position);
    myRenderItem = new RenderItem(shape, &this->myTransform, color);
}

Entity::~Entity() {
    myRenderItem->release();
}

void 
Entity::enableRender() {
    if (myRenderItem != nullptr) RegisterRenderItem(myRenderItem);
}