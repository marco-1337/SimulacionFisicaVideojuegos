#include "IntegrableEntity.hpp"
#include <cmath>
#include <limits>

#include <iostream>

IntegrableEntity::IntegrableEntity (Vector3 position, Shape *shape, Vector4 color, Vector3 velocity, 
    Integrator integrator, double mass)
: Entity(position, shape, color),
velocity(velocity),
acceleration(acceleration),
force(0.),
integrator(integrator),
mass(mass)
{
    //if (integrator == VERLET) this->integrator = PRE_VERLET;

    if (mass <= 0.) {
        this->mass = 0.0;

        this->inverseMass = std::numeric_limits<double>::max();
    }   
    else {
        this->inverseMass = 1./mass;
    }
}

IntegrableEntity::~IntegrableEntity() {}

void 
IntegrableEntity::update(double t) {
    integrate(t);
}

void
IntegrableEntity::addForce(Vector3 f) { force += f; }

void
IntegrableEntity::integrate(double t) {

    // Calcula la acceleración

    acceleration = force * inverseMass;
    force = Vector3(0.);

    // Integra con la acceleracion

    switch (integrator) {
        case EULER:

            myTransform.p += velocity * t;
            velocity += acceleration * t;

            // Damping
            velocity *= std::pow(DAMPING, t);

            break;
        
        case SYMPLECTIC_EULER:

            velocity += acceleration * t;
            myTransform.p += velocity * t;

            // Damping
            velocity *= std::pow(DAMPING, t);
            
            break;
        
        /*case VERLET:

            currentPosition = myTransform.p;
            myTransform.p = 2.0 * myTransform.p - previousPosition + acceleration * t * t;
            previousPosition = currentPosition;

            break;
        
        case PRE_VERLET:

            // Desarrollo de Taylor en 2do orden
            previousPosition = myTransform.p;
            myTransform.p = myTransform.p + velocity * t + 0.5 * acceleration * t * t;

            integrator = VERLET;

            break;
        */
    }
}