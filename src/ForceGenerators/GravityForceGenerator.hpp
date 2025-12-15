#pragma once

#include "Entity.hpp"
#include <memory>
#include <list>

#include "ForceGenerator.hpp"

class EntityContainer;

class GravityForceGenerator: public ForceGenerator {
public:
    GravityForceGenerator(double gravity);
    virtual void tryAddForce(Entity& ent, double dt);

private:
    double gravity;
};