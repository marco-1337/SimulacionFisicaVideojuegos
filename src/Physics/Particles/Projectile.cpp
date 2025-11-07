#include "Projectile.hpp"
#include <iostream>

using namespace std;

#include <iostream>

Projectile::Projectile(Vector3 position, Shape *shape, Vector4 color, Integrator integrator, 
    double timeToDie, double mass, Vector3 shootDirection, double speed, double simulatedSpeed)
: Particle(position, shape, color, shootDirection, integrator, mass, timeToDie) {
    
    velocity.normalize();
    velocity *= simulatedSpeed;

    simulatedMass = mass * pow(speed / simulatedSpeed, 2);
}

double
Projectile::getMass() const {
    return mass/simulatedMass; 
}