#include "ExplosionForceGenerator.hpp"

#include "ParticleComponent.hpp"
#include "DynamicRigidbodyComponent.hpp"

#include "Timer.hpp"

#include <cmath>
#include <iostream>

ExplosionForceGenerator::ExplosionForceGenerator(std::shared_ptr<Timer> timer, Vector3 position, 
    double explosionRadius, double explosionForce)

: timer(timer),
position(position),
explosionRadius(explosionRadius),
explosionForce(explosionForce),
time(timer->getTotalTime()),
thau(time/4.)
{}

void 
ExplosionForceGenerator::tryAddForce(Entity& ent, double dt) {

    if (timer->isAlive()) {

        bool hasParticle = ent.hasComponent<ParticleComponent>();
        bool hasDynamicRigid = ent.hasComponent<DynamicRigidbodyComponent>();

        if (hasParticle ||  hasDynamicRigid) {
            ParticleComponent &pComponent = ent.getComponent<ParticleComponent>();
            
            Vector3 dirVec = ent.getPos() - position;
            double r = dirVec.magnitude();

            if (r < explosionRadius && r > 0.0) {
                
                dirVec.normalize();

                Vector3 explosionForceVector = 
                    (explosionForce / (r * r)) * 
                    (ent.getPos() - position) * 
                    std::exp(-(timer->getCurrentTime()/thau));

                if (hasParticle) {
                    ent.getComponent<ParticleComponent>().addForce(explosionForceVector);
                }
                else {
                    ent.getComponent<DynamicRigidbodyComponent>().addForceAtCenterOfMass(explosionForceVector);
                }
            }
        }
    }
    else {
        alive = false;
    }
}