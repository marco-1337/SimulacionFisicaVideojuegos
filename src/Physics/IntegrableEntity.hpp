#pragma once

#include "Entity.hpp"

enum Integrator {
    EULER,
    SYMPLECTIC_EULER/*,
    VERLET,
    PRE_VERLET*/
};

class IntegrableEntity: public Entity {
public:
    IntegrableEntity(Vector3 pos, Shape *shape, Vector4 color, Vector3 velocity, Integrator integrator, double mass = 1.);
    virtual ~IntegrableEntity() = 0;

    virtual void update(double t) override;
    virtual void integrate(double t);
    virtual void addForce(Vector3 f) override;
    inline virtual double getMass() const override { return mass; }

protected:

    static constexpr double DAMPING = 0.99;

    Integrator integrator;
    Vector3 velocity, acceleration, force;
    //Vector3 previousPosition, currentPosition;
    double mass, inverseMass;
};