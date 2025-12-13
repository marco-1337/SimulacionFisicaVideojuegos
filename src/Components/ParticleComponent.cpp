#include "ParticleComponent.hpp"
#include "Entity.hpp"
#include <limits>
#include <cmath>

using namespace physx;

ParticleComponent::ParticleComponent(Vector3, Integrator integrator, double mass)
: Component() {

    this->velocity = velocity;
    this->integrator = integrator;
    this->mass = mass;

    //if (integrator == VERLET) this->integrator = PRE_VERLET;
    if (mass <= 0.) {
        this->mass = 0.0;

        this->inverseMass = (std::numeric_limits<double>::max)();
    }   
    else {
        this->inverseMass = 1./mass;
    }
}

void
ParticleComponent::update(Entity& ent, double t) {
// Calcula la acceleración

    acceleration = force * inverseMass;
    force = Vector3(0.);

    // Integra con la acceleracion

    switch (integrator) {
        case EULER:

            ent.translate(velocity * t);
            velocity += acceleration * t;

            // Damping
            velocity *= std::pow(DAMPING, t);

            break;
        
        case SYMPLECTIC_EULER:

            velocity += acceleration * t;
            ent.translate(velocity * t);

            // Damping
            velocity *= std::pow(DAMPING, t);
            
            break;
        
        /*case VERLET:

            currentPosition = ent.getPos();
            ent.setPos(2.0 * myTransform.p - previousPosition + acceleration * t * t);
            previousPosition = currentPosition;

            break;
        
        case PRE_VERLET:

            // Desarrollo de Taylor en 2do orden
            previousPosition = ent.getPos();
            ent.setPos(previousPosition + velocity * t + 0.5 * acceleration * t * t);

            integrator = VERLET;

            break;
        */
    }
}

void
ParticleComponent::addForce(Vector3 f) { 
    force += f; 
}