#pragma once

#include <list>
#include <memory>
#include "KillableList.hpp"

#include "Entity.hpp"
#include "ParticleSystem.hpp"
#include "ForceGenerator.hpp"

// Tendria que heredar de una interfaz, la misma de la que deba heredar entity container
// que fuerce a implementar update y enableRendering
class Scene {
public:
    Scene();
    virtual ~Scene() = 0 {}
    virtual void keyPress(unsigned char key) {}
    virtual void update(double dt);
    void enableRendering();
protected:

    KillableList<Entity> sceneEntities;

    KillableList<ParticleSystem> particleSystems;
    KillableList<ForceGenerator> forceGenerators;
};