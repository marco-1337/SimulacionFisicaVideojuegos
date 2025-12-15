#include "GravityForceGenerator.hpp"

#include "ParticleComponent.hpp"

GravityForceGenerator::GravityForceGenerator(double gravity)
:gravity(gravity) {}

void 
GravityForceGenerator::tryAddForce(Entity& ent, double dt) {

    if (ent.hasComponent<ParticleComponent>()) {
        ParticleComponent &pComponent = ent.getComponent<ParticleComponent>();
        pComponent.addForce(Vector3(0., pComponent.getMass() * gravity, 0.));
    }
}