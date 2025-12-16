#include "DustDiskParticleGenerator.hpp"

#include <cmath>

#include "Entity.hpp"
#include "ParticleComponent.hpp"
#include "TimeDeletableComponent.hpp"
#include "ParticleSystem.hpp"

#include "consts.hpp"

using namespace physx;

DustDiskParticleGenerator::DustDiskParticleGenerator(Vector3 pos, double radius, double minLaunchSpeed, 
    double maxLaunchSpeed, double particleMinDuration, double particleMaxDuration, Vector4 particleColor, 
    double particleSize, double generationDuration, double generationProbability, double minTriesPerSecond, 
    double maxTriesPerSecond, std::shared_ptr<bool> enabledFlag)
: ParticleGenerator(generationDuration, generationProbability, minTriesPerSecond, 
    maxTriesPerSecond, enabledFlag),
position(pos),
radius(radius),
minLaunchSpeed(minLaunchSpeed),
maxLaunchSpeed(maxLaunchSpeed),
particleMinDuration(particleMinDuration), 
particleMaxDuration(particleMaxDuration),
particleColor(particleColor) {
    
    particleGeometry = PxSphereGeometry(particleSize);
}

std::unique_ptr<Entity> 
DustDiskParticleGenerator::generateParticle(double dt) { 

    double angle = gaussianRand->mapRange(0., PI);
    double module = gaussianRand->mapRange(-radius, radius); 

    double absModule = std::abs(module);
    absModule = (absModule > radius / 2.) ? radius - absModule : absModule;

    double multiplier = 0.5 + (absModule / (radius/2)) * (2. - 0.5);

    std::unique_ptr<Entity> ent = std::make_unique<Entity>(
        Vector3(std::cos(angle) * module, 0., std::sin(angle) * module) + position,
        particleGeometry, particleColor);

    ent->addComponent<ParticleComponent>(std::make_unique<ParticleComponent>(
        Vector3(0., gaussianRand->mapRange(minLaunchSpeed, maxLaunchSpeed) * multiplier, 0.),
        Integrator::SYMPLECTIC_EULER, 0.1));
    
    ent->addComponent<TimeDeletableComponent>(std::make_unique<TimeDeletableComponent>(
        gaussianRand->mapRange(particleMinDuration, particleMaxDuration)));

    return ent;
}