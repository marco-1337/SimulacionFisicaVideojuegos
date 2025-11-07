#pragma once

#include <list>
#include <memory>

#include "GravityForceGenerator.hpp"

class Entity;
class ParticleSystem;
class EntityContainer;

// Tendria que heredar de una interfaz, la misma de la que deba heredar entity container
// que fuerce a implementar update y enableRendering
class Scene {
public:
    Scene();
    virtual ~Scene() = 0 {}
    virtual void keyPress(unsigned char key) {}
    virtual void update(double dt);
    virtual void enableRendering();
protected:
    std::shared_ptr<EntityContainer> sceneEntities;
    std::unique_ptr<GravityForceGenerator> gravityForce;
};