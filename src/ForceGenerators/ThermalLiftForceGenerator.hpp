#pragma once

#include "Entity.hpp"

#include "ForceGenerator.hpp"

class ThermalLiftForceGenerator: public ForceGenerator {
public:
    ThermalLiftForceGenerator(double thermalLiftCoeficient);
    virtual void tryAddForce(Entity& ent, double dt);

private:
    double thermalLiftCoeficient;
};