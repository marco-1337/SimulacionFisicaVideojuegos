#pragma once

#include "Entity.hpp"

#include "ForceGenerator.hpp"

class EntityContainer;

class BuoyancyForceGenerator: public ForceGenerator {
public:
    BuoyancyForceGenerator(double waterSurfaceHeight);
    virtual void tryAddForce(Entity& ent, double dt);

private:
    double waterSurfaceHeight;
};