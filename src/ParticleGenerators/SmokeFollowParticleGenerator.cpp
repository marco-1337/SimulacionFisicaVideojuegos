#include "SmokeFollowParticleGenerator.hpp"

#include <cmath>

#include "Entity.hpp"
#include "ParticleComponent.hpp"
#include "TimeDeletableComponent.hpp"
#include "ParticleSystem.hpp"

#include "consts.hpp"

using namespace physx;

SmokeFollowParticleGenerator::SmokeFollowParticleGenerator(std::weak_ptr<Entity> followEntity, 
        physx::PxGeometry& particleGeometry, double minLaunchSpeed, double maxLaunchSpeed, 
        double launchMaxAngle, double particleDuration, double generationDuration, 
        double generationProbability, double minTriesPerSecond, double maxTriesPerSecond, 
        std::shared_ptr<bool> enabledFlag)
: ParticleGenerator(generationDuration, generationProbability, minTriesPerSecond, maxTriesPerSecond, enabledFlag),
followEntity(followEntity),
minLaunchSpeed(minLaunchSpeed),
maxLaunchSpeed(maxLaunchSpeed),
launchMaxAngle(launchMaxAngle),
particleDuration(particleDuration), 
particleGeometry(particleGeometry) {}

std::unique_ptr<Entity> 
SmokeFollowParticleGenerator::generateParticle(double dt) {

    if (std::shared_ptr<Entity> ent = followEntity.lock()) {
        if (ent->isAlive()) {
            double angle = PI + uniformRand->mapRange(-launchMaxAngle, launchMaxAngle);
            double x = cos(angle);
            double z = uniformRand->mapRange(0., x);
            double y = sin(angle);

            double module = uniformRand->mapRange(0., launchMaxAngle);

            return entidad;
        }
    }
    else {
        alive = false;
        return nullptr;
    }
}