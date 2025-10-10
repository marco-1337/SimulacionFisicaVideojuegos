#include "Projectile.hpp"
#include <iostream>

using namespace std;

Projectile::Projectile(Vector3 position, Shape *shape, Vector4 color, Integrator integrator, 
        double damping, double timeToDie, double mass, Vector3 shootDirection, 
        double speed, double simulatedSpeed)
: Particle(position, shape, color, shootDirection, Vector3(0.), integrator, damping, timeToDie),
speed(speed),
simulatedSpeed(simulatedSpeed) {
    
    velocity.normalize();
    velocity *= simulatedSpeed;
    
    calculateGravity();
}

void
Projectile::calculateGravity() {
    simulatedMass = mass * pow(speed / simulatedSpeed, 2);
    acceleration = GRAVITY * (mass/simulatedMass);
    cout << acceleration.x << " " << acceleration.y << " " << acceleration.z << "\n";
}