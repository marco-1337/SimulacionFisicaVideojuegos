#include "BuoyancyForceGenerator.hpp"

#include "ParticleComponent.hpp"
#include "Entity.hpp"
#include "ParticleComponent.hpp"
#include "DynamicRigidbodyComponent.hpp"

#include "consts.hpp"

BuoyancyForceGenerator::BuoyancyForceGenerator(double waterSurfaceHeight)
:waterSurfaceHeight(waterSurfaceHeight) {}

void 
BuoyancyForceGenerator::tryAddForce(Entity& ent, double dt) {

    bool hasParticle = ent.hasComponent<ParticleComponent>();
    bool hasDynamicRigid = ent.hasComponent<DynamicRigidbodyComponent>();

    if (hasParticle ||  hasDynamicRigid) {

        double h = ent.getPos().y;
        double objectHeight = ent.getBoundsHeight();

        double immersed;

        double bottom = h - objectHeight * 0.5;
        double top = h + objectHeight * 0.5;

        if (bottom >= waterSurfaceHeight) {
            immersed = 0.0;
        }
        else if (top <= waterSurfaceHeight) {
            immersed = 1.0;
        }
        else {
            immersed = (waterSurfaceHeight - bottom) / objectHeight;
        }

        Vector3 buoyancyForce = Vector3(
            0., 
            WATER_DENSITY * ent.getApproximatedVolume() * immersed * -GRAVITY_FORCE * BUOYANCY_DAMPING, 
            0.);

        if (hasParticle) {
            ent.getComponent<ParticleComponent>().addForce(buoyancyForce);
        }
        else {
            ent.getComponent<DynamicRigidbodyComponent>().addForceAtCenterOfMass(buoyancyForce);
        }
    }
}