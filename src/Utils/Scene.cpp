#include "Scene.hpp"

#include "Entity.hpp"
#include "ParticleSystem.hpp"

using namespace physx;

Scene::Scene(): PhysicsSceneContainer(), sceneEntities(), sceneForceGeneratorsRegistry(), particleSystems() {}

Scene::~Scene() {}

void
Scene::update(double dt) {

    timers.foreachAlive( [dt] (Timer& timer) {
        timer.addTime(dt);
    });

    sceneEntities.foreachAlive( [this, dt](Entity& e) { 

        for (auto forceGen : sceneForceGeneratorsRegistry) {
            forceGen->tryAddForce(e, dt);
        }
        e.update(dt); 
    });

    for (auto system : particleSystems) {
        system->update(dt);
    }

    for (auto it = sceneForceGeneratorsRegistry.begin(); it != sceneForceGeneratorsRegistry.end(); ) {
        if (!(*it)->isAlive()) it = sceneForceGeneratorsRegistry.erase(it);
        else ++it;
    }
}

void
Scene::enableRendering() {
    sceneEntities.foreachAlive( [](Entity& e) { e.enableRender(); });

    for (auto system : particleSystems) {
        system->enableRender();
    }
}

void 
Scene::simulate(double dt) { myPhysxScene->simulate(dt); }

bool 
Scene::fetchResults(bool block) { return myPhysxScene->fetchResults(block); }

void 
Scene::onCollision(physx::PxActor* actor1, physx::PxActor* actor2)
{
	PX_UNUSED(actor1);
	PX_UNUSED(actor2);
}

std::shared_ptr<Timer> 
Scene::addTimer(double t) {

    std::shared_ptr<Timer> timer = Timer::Create(t);

    timers.addObject(timer);

    return timer;
}