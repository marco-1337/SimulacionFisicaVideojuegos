#include "Scene.hpp"

#include "Entity.hpp"
#include "ParticleSystem.hpp"

Scene::Scene(): sceneEntities(), particleSystems() {}

void
Scene::update(double dt) {
    sceneEntities.foreachAlive( [dt](Entity& e) { e.update(dt); });
    particleSystems.foreachAlive( [dt](ParticleSystem& pSys) { pSys.update(dt); } );
}

void
Scene::enableRendering() {
    sceneEntities.foreachAlive( [](Entity& e) { e.enableRender(); });
    particleSystems.foreachAlive( [](ParticleSystem& pSys) { pSys.enabledRender(); } );
}