#pragma once

#include "Component.hpp"

#include "physxDefs.hpp"

enum Integrator {
    EULER,
    SYMPLECTIC_EULER/*,
    VERLET,
    PRE_VERLET*/
};

class ParticleComponent: public Component {
public: 
    ParticleComponent(const Vector3& velocity, Integrator integrator, double mass);

    virtual void update(Entity& ent,  double t) override;
    void addForce(Vector3 f);
    virtual double getMass() const;
protected:    
    static constexpr double DAMPING = 0.99;

    Integrator integrator;
    Vector3 velocity, acceleration, force;
    //Vector3 previousPosition, currentPosition;
    double mass, inverseMass;
};