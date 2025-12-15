#include "Scene.hpp"

#include "Entity.hpp"
#include "ParticleSystem.hpp"

using namespace physx;

Scene::Scene(): PhysicsSceneContainer(), sceneEntities(), sceneForceGeneratorsRegistry(), particleSystems() {}

Scene::~Scene() {}

void
Scene::update(double dt) {

    sceneEntities.foreachAlive( [this, dt](Entity& e) { 

        for (auto forceGen : sceneForceGeneratorsRegistry) {
            forceGen->tryAddForce(e, dt);
        }
        e.update(dt); 
    });

    for (size_t i = 0; i < particleSystems.size(); ++i) {
        particleSystems[i].update(dt);
    }

    for (auto it = sceneForceGeneratorsRegistry.begin(); it != sceneForceGeneratorsRegistry.end(); ) {
        if (!(*it)->isAlive()) it = sceneForceGeneratorsRegistry.erase(it);
        else ++it;
    }
}

void
Scene::enableRendering() {
    sceneEntities.foreachAlive( [](Entity& e) { e.enableRender(); });

    for (size_t i = 0; i < particleSystems.size(); ++i) {
        particleSystems[i].enableRender();
    }
}

void 
Scene::simulate(double dt) { myPhysxScene->simulate(dt); }

bool 
Scene::fetchResults(bool block) { return myPhysxScene->fetchResults(block); }