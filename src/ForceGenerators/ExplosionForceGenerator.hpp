#pragma once

#include "Entity.hpp"

#include "ForceGenerator.hpp"

class EntityContainer;

class Timer;

class ExplosionForceGenerator: public ForceGenerator {
public:
    ExplosionForceGenerator(std::shared_ptr<Timer> timer, Vector3 position, double explosionRadius
        , double explosionForce);
    virtual void tryAddForce(Entity& ent, double dt);

private:
    Vector3 position;
    double time, explosionRadius, thau, explosionForce;

    std::shared_ptr<Timer> timer;
};