#include "Scene0.hpp"

#include <memory>

#include "RenderUtils.hpp"

using namespace physx;

Scene0::Scene0() {

    PxSphereGeometry geometry = PxSphereGeometry(0.5f);

    std::unique_ptr<Entity> axisCentral = std::make_unique<Entity>(Vector3(0.), geometry, Vector4(1.));
    sceneEntities.addObject(std::move(axisCentral));

    axisCentral = std::make_unique<Entity>(Vector3(10., 0., 0.), geometry, Vector4(1., 0., 0., 1.));
    sceneEntities.addObject(std::move(axisCentral));
    
    axisCentral = std::make_unique<Entity>(Vector3(0., 10., 0.), geometry, Vector4(0., 1., 0., 1.));
    sceneEntities.addObject(std::move(axisCentral));

    axisCentral = std::make_unique<Entity>(Vector3(0., 0., 10.), geometry, Vector4(0., 0., 1., 1.));
    sceneEntities.addObject(std::move(axisCentral));
}