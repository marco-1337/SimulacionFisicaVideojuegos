#pragma once

#include "Entity.hpp"

#include "ForceGenerator.hpp"

class GravityForceGenerator: public ForceGenerator {
public:
    GravityForceGenerator(double gravity);
    virtual void tryAddForce(Entity& ent, double dt);

private:
    double gravity;
};