#pragma once

#include "PhysicsSceneContainer.hpp"

#include <vector>
#include <memory>
#include <unordered_set>

#include "KillableList.hpp"

#include "Entity.hpp"
#include "ParticleSystem.hpp"
#include "ForceGenerator.hpp"

#include "Timer.hpp"

#include "callbacks.hpp"

// Tendria que heredar de una interfaz, la misma de la que deba heredar entity container
// que fuerce a implementar update y enableRendering
class Scene: public PhysicsSceneContainer {
public:
    Scene();
    virtual ~Scene() = 0;
    virtual void keyPress(unsigned char key) {}
    virtual void update(double dt);
    void enableRendering();

    void simulate(double dt);
	bool fetchResults(bool block);

protected:
    std::shared_ptr<Timer> addTimer(double t);

    KillableList<Timer> timers;

    KillableList<Entity> sceneEntities;
    std::unordered_set<std::shared_ptr<ForceGenerator>> sceneForceGeneratorsRegistry;

    std::vector<ParticleSystem> particleSystems;
};