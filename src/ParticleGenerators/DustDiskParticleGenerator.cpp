#include "DustDiskParticleGenerator.hpp"

#include <cmath>

#include "Entity.hpp"
#include "ParticleComponent.hpp"
#include "DynamicRigidbodyComponent.hpp"
#include "TimeDeletableComponent.hpp"
#include "ParticleSystem.hpp"

#include "consts.hpp"

using namespace physx;

DustDiskParticleGenerator::DustDiskParticleGenerator(Vector3 pos, double radius, double minLaunchSpeed, 
    double maxLaunchSpeed, double particleMinDuration, double particleMaxDuration, Vector4 particleColor, 
    double generationDuration, double minTriesPerSecond, double maxTriesPerSecond, 
    physx::PxGeometry& particleGeometry, physx::PxScene *physicalScene,
    std::shared_ptr<CubeAreaDeleterComponent> cubeDeleter, std::shared_ptr<bool> enabledFlag)

: ParticleGenerator(generationDuration, minTriesPerSecond, maxTriesPerSecond, particleGeometry, 
    1.5, cubeDeleter, enabledFlag),
position(pos),
radius(radius),
minLaunchSpeed(minLaunchSpeed),
maxLaunchSpeed(maxLaunchSpeed),
particleMinDuration(particleMinDuration), 
particleMaxDuration(particleMaxDuration),
particleColor(particleColor),
physicalScene(physicalScene) {}

std::unique_ptr<Entity> 
DustDiskParticleGenerator::generateParticle(double dt) { 

    double angle = uniformRand->mapRange(0., 2*PI);
    double module = gaussianRand->mapRange(0, radius); 

    double absModule = (module > radius / 2.) ? radius - module : module;

    double multiplier = 0.5 + (absModule / (radius/2)) * (2. - 0.5);

    std::unique_ptr<Entity> ent = std::make_unique<Entity>(
        Vector3(std::cos(angle) * module, 0., std::sin(angle) * module) + position,
        *particleGeometry, particleColor);

    ent->addComponent<TimeDeletableComponent>(std::make_unique<TimeDeletableComponent>(
        gaussianRand->mapRange(particleMinDuration, particleMaxDuration)));

    Vector3 shootVector = Vector3(0., gaussianRand->mapRange(minLaunchSpeed, maxLaunchSpeed) * multiplier, 0.);

    if (gGenerateRigidbody) {
        ent->addComponent<DynamicRigidbodyComponent>(std::make_unique<DynamicRigidbodyComponent>(
            *ent, physicalScene, shootVector, Vector3(0.), 150., 1., 1., 0.));
    }
    else {
        ent->addComponent<ParticleComponent>(std::make_unique<ParticleComponent>(shootVector, 
            Integrator::SYMPLECTIC_EULER, 150.));
    }

    return ent;
}