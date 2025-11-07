#pragma once

#include "IntegrableEntity.hpp"

class Particle: public IntegrableEntity{
public:
    Particle(Vector3 position, Shape *shape, Vector4 color, Vector3 velocity, Integrator integrator, 
        double mass);

    Particle(Vector3 position, Shape *shape, Vector4 color, Vector3 velocity, Integrator integrator, 
        double mass, double timeToDie); 

    Particle(Vector3 position, Shape *shape, Vector4 color, Vector3 velocity, Integrator integrator, 
        double mass, Vector3 originDeletePos, double deleteDistance);

    Particle(Vector3 position, Shape *shape, Vector4 color, Vector3 velocity, Integrator integrator, 
        double mass,double timeToDie, Vector3 originDeletePos, double deleteDistance);
    

    virtual void update(double t) override;

protected:

    bool timeDeletable, distanceDeletable;

    double timeToDie, aliveTime, deleteDistance;

    Vector3 originDeletePos;
};