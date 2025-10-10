#include "Scene0.hpp"

#include "Entity.hpp"
#include "RenderUtils.hpp"

using namespace physx;

Scene0::Scene0() {

    PxTransform *transform = new PxTransform(PxVec3(0., 0., 0.));
    transformList.push_back(transform);
	PxSphereGeometry geometry = PxSphereGeometry(1.0f);
	PxShape *shape = CreateShape(geometry);

	RenderItem *item = new RenderItem(shape, transform, PxVec4(1., 1., 1., 1.));
	axis.push_back(item);

	transform = new PxTransform(PxVec3(10., 0., 0.));
    transformList.push_back(transform);
	item = new RenderItem(shape, transform, PxVec4(1., 0., 0., 1.));
	axis.push_back(item);

	transform = new PxTransform(PxVec3(0., 10., 0.));
    transformList.push_back(transform);
    item = new RenderItem(shape, transform, PxVec4(0., 1., 0., 1.));
	axis.push_back(item);
	
	transform = new PxTransform(PxVec3(0., 0., 10.));
    transformList.push_back(transform);
    item = new RenderItem(shape, transform, PxVec4(0., 0., 1., 1.));
	axis.push_back(item);
}

Scene0::~Scene0() {
    for (RenderItem *e : axis) {
        e->release();
    }  
    for (PxTransform *e : transformList) {
        delete e;
        e = nullptr;
    }
}

void
Scene0::enableRendering() {
    for (RenderItem *e : axis) {
        RegisterRenderItem(e);
    }
}