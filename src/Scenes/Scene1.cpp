#include "Scene1.hpp"

#include <memory>

#include "RenderUtils.hpp"

using namespace physx;

Scene1::Scene1() {

    PxSphereGeometry geometry = PxSphereGeometry(0.5f);
	PxShape *particleShape = CreateShape(geometry);

    std::unique_ptr<Entity> axisCentral = std::make_unique<Entity>(Vector3(0.), particleShape, Vector4(1.));
    sceneEntities.addObject(std::move(axisCentral));

    axisCentral = std::make_unique<Entity>(Vector3(10., 0., 0.), particleShape, Vector4(1.));
    sceneEntities.addObject(std::move(axisCentral));
    
    axisCentral = std::make_unique<Entity>(Vector3(0., 10., 0.), particleShape, Vector4(1.));
    sceneEntities.addObject(std::move(axisCentral));
    
    axisCentral = std::make_unique<Entity>(Vector3(0., 0., 10.), particleShape, Vector4(1.));
    sceneEntities.addObject(std::move(axisCentral));

    particleShape->release();
}