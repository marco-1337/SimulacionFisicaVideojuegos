#pragma once

#include "Entity.hpp"
#include <memory>
#include <list>

#include "ForceGenerator.hpp"

class EntityContainer;

class ThermalLiftForceGenerator: public ForceGenerator {
public:
    ThermalLiftForceGenerator(double thermalLiftCoeficient);
    virtual void tryAddForce(Entity& ent, double dt);

private:
    double thermalLiftCoeficient;
};