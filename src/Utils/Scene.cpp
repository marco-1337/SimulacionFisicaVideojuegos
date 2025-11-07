#include "Scene.hpp"
#include "EntityContainer.hpp"
#include "EntityContainer.hpp"

Scene::Scene()
: sceneEntities(std::make_shared<EntityContainer>()),
gravityForce(std::make_unique<GravityForceGenerator>(GRAVITY)) {
    gravityForce->registerEntityGroup(sceneEntities);
}

void
Scene::update(double dt) {
    gravityForce->applyForce();
    sceneEntities->update(dt);
}

void
Scene::enableRendering() {
    sceneEntities->enableRendering();
}