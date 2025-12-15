#include "ProjectileParticleComponent.hpp"

ProjectileParticleComponent::ProjectileParticleComponent(const Vector3& shootDirection, Integrator integrator, 
    double mass, double speed, double simulatedSpeed)
: ParticleComponent(shootDirection, integrator, mass) {

    velocity.normalize();
    velocity *= simulatedSpeed;

    simulatedMass = mass * pow(speed / simulatedSpeed, 2);
}

double
ProjectileParticleComponent::getMass() const {
    return mass/simulatedMass; 
}