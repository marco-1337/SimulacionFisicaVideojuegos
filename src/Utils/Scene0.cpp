#include "Scene0.hpp"

#include "Entity.hpp"
#include "RenderUtils.hpp"
#include "EntityContainer.hpp"

using namespace physx;

Scene0::Scene0(): Scene() {

	PxSphereGeometry geometry = PxSphereGeometry(0.5f);
	PxShape *shape = CreateShape(geometry);

    sceneEntities->addEntity(new Entity(Vector3(0., 0., 0), shape, Vector4(1.)));

    sceneEntities->addEntity(new Entity(Vector3(10., 0., 0), shape, Vector4(1., 0., 0., 1.)));
    sceneEntities->addEntity(new Entity(Vector3(5., 0., 0), shape, Vector4(1., 0., 0., 1.)));

    sceneEntities->addEntity(new Entity(Vector3(0., 10., 0), shape, Vector4(0., 1., 0., 1.)));
    sceneEntities->addEntity(new Entity(Vector3(0., 5., 0), shape, Vector4(0., 1., 0., 1.)));

    sceneEntities->addEntity(new Entity(Vector3(0., 0., 10.), shape, Vector4(0., 0., 1., 1.)));
    sceneEntities->addEntity(new Entity(Vector3(0., 0., 5.), shape, Vector4(0., 0., 1., 1.)));

    shape->release();
}

Scene0::~Scene0() {}