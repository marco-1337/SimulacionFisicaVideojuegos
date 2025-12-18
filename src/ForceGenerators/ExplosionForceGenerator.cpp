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

        if (ent.hasComponent<ParticleComponent>()) {
            ParticleComponent &pComponent = ent.getComponent<ParticleComponent>();
            
            Vector3 dirVec = ent.getPos() - position;
            double r = dirVec.magnitude();

            if (r < explosionRadius) {

                dirVec.normalize();

                pComponent.addForce(
                    (explosionForce / (r * r)) * 
                    ent.getPos() - position * 
                    std::exp(-(timer->getCurrentTime()/thau))
                );
            }
        }
        else if (ent.hasComponent<DynamicRigidbodyComponent>()) {
            DynamicRigidbodyComponent &pComponent = ent.getComponent<DynamicRigidbodyComponent>();
            
            Vector3 dirVec = ent.getPos() - position;
            double r = dirVec.magnitude();

            if (r < explosionRadius) {
                pComponent.addForceAtCenterOfMass((explosionForce / (r * r)) * 
                    ent.getPos() - position * 
                    std::exp(-(timer->getCurrentTime()/thau))
                );
            }
        }
    }
    else {
        std::cout << "muelto \n";
        alive = false;
    }
}