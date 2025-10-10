#pragma once

#include "Entity.hpp"

enum Integrator {
    EULER,
    SYMPLECTIC_EULER,
    VERLET,
    PRE_VERLET
};

class IntegrableEntity: public Entity {
public:
    IntegrableEntity(Vector3 pos, Shape *shape, Vector4 color, Vector3 velocity, Vector3 accel, 
        Integrator integrator, double damping = 0.99);
    virtual ~IntegrableEntity() = 0;

    virtual void update(double t) override;
    virtual void integrate(double t);
protected:
    Integrator integrator;
    Vector3 velocity;
    Vector3 acceleration;
    Vector3 previousPosition;
    Vector3 currentPosition;
    double damping;
};