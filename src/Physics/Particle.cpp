#include "Particle.hpp"
#include "RenderUtils.hpp"

#include <iostream>
#include <cmath>

using namespace physx;

Particle::Particle(Vector3 position, Shape *shape, Vector4 color, Vector3 velocity, Vector3 acceleration, 
    Integrator integrator, double damping, double timeToDie, bool deleteable)
: IntegrableEntity(position, shape, color, velocity, acceleration, integrator, damping), 
timeToDie(timeToDie),
aliveTime(0.),
deleteable(deleteable) {}

Particle::~Particle() {}

void
Particle::update(double t) {

    aliveTime += t;
    IntegrableEntity::update(t);
}

bool
Particle::needToDelete() {
    return aliveTime > timeToDie && deleteable;
}