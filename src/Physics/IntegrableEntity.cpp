#include "IntegrableEntity.hpp"
#include <cmath>

IntegrableEntity::IntegrableEntity (Vector3 position, Shape *shape, Vector4 color, Vector3 velocity, Vector3 acceleration, 
        Integrator integrator, double damping)
: Entity(position, shape, color),
velocity(velocity),
acceleration(acceleration),
integrator(integrator),
damping(damping) {
    if (integrator == VERLET) this->integrator = PRE_VERLET;
}

IntegrableEntity::~IntegrableEntity() {}

void 
IntegrableEntity::update(double t) {
    integrate(t);
}

void
IntegrableEntity::integrate(double t) {

    switch (integrator) {
        case EULER:

            myTransform.p += velocity * t;
            velocity += acceleration * t;

            // Damping
            velocity *= std::pow(damping, t);

            break;
        
        case SYMPLECTIC_EULER:

            velocity += acceleration * t;
            myTransform.p += velocity * t;

            // Damping
            velocity *= std::pow(damping, t);
            
            break;
        
        case VERLET:

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
    }
}