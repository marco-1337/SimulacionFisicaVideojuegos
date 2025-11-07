#include "Particle.hpp"
#include "RenderUtils.hpp"

#include <iostream>
#include <cmath>

using namespace physx;

Particle::Particle(Vector3 position, Shape *shape, Vector4 color, Vector3 velocity, Integrator integrator, double mass)
: IntegrableEntity(position, shape, color, velocity, integrator, mass),
timeDeletable(false),
distanceDeletable(false),
aliveTime(),
timeToDie(),
originDeletePos(),
deleteDistance()
{}

Particle::Particle(Vector3 position, Shape *shape, Vector4 color, Vector3 velocity, Integrator integrator, 
    double mass, double timeToDie)
: IntegrableEntity(position, shape, color, velocity, integrator, mass),
timeDeletable(true),
distanceDeletable(false),
aliveTime(0.),
timeToDie(timeToDie),
originDeletePos(),
deleteDistance()
{}

Particle::Particle(Vector3 position, Shape *shape, Vector4 color, Vector3 velocity, Integrator integrator, 
    double mass, Vector3 originDeletePos, double deleteDistance)
: IntegrableEntity(position, shape, color, velocity, integrator, mass),
timeDeletable(false),
distanceDeletable(true),
aliveTime(),
timeToDie(),
originDeletePos(originDeletePos),
deleteDistance(deleteDistance)
{}

Particle::Particle(Vector3 position, Shape *shape, Vector4 color, Vector3 velocity, Integrator integrator, 
    double mass, double timeToDie, Vector3 originDeletePos, double deleteDistance)
: IntegrableEntity(position, shape, color, velocity, integrator, mass),
timeDeletable(true),
distanceDeletable(true),
aliveTime(0.),
timeToDie(timeToDie),
originDeletePos(originDeletePos),
deleteDistance(deleteDistance)
{}

void
Particle::update(double t) {

    if (timeDeletable) {
        aliveTime += t;
        alive = aliveTime < timeToDie;
    }

    if (distanceDeletable) {
        alive = (myTransform.p - originDeletePos).magnitude() >= deleteDistance;
    }

    IntegrableEntity::update(t);
}