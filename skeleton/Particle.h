#pragma once

#include <PxPhysicsAPI.h>

class RenderItem;

using Vector3 = physx::PxVec3;

class Particle {
public:
    enum Integrator {
        EULER,
        SYMPLECTIC_EULER,
        VERLET,
        PRE_VERLET
    };

    Particle(Vector3 pos, Vector3 vel, Vector3 accel, Integrator integrator, double dampingVal = 0.99, double timeToDie = 5.);
    ~Particle();

    void integrate(double t);
    bool isDead();

private:

    Integrator integrator;
    Vector3 vel;
    Vector3 accel;
    physx::PxTransform pose;
    Vector3 prevPos;
    Vector3 currPos;
    double dampingVal = 1.;
    RenderItem *renderItem;
    double timeToDie; 
    double aliveTime;
};