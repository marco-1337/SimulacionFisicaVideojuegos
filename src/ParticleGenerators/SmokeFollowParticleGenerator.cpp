#include "SmokeFollowParticleGenerator.hpp"

#include <cmath>

#include "Entity.hpp"
#include "ParticleComponent.hpp"
#include "DynamicRigidbodyComponent.hpp"
#include "TimeDeletableComponent.hpp"
#include "ParticleSystem.hpp"
#include "TemperatureComponent.hpp"

#include "consts.hpp"

using namespace physx;

SmokeFollowParticleGenerator::SmokeFollowParticleGenerator(std::weak_ptr<Entity> followEntity, 
        double yGenerationOffset, double maxCoolingHeight, double minCoolingHeight, double minLaunchSpeed, 
        double maxLaunchSpeed, double launchMaxAngle, double particleDuration, double generationDuration, 
        double minTriesPerSecond, double maxTriesPerSecond, physx::PxGeometry& particleGeometry, 
        physx::PxScene *physicalScene, std::shared_ptr<CubeAreaDeleterComponent> cubeDeleter, 
        std::shared_ptr<bool> enabledFlag)

: ParticleGenerator(generationDuration, minTriesPerSecond, maxTriesPerSecond, particleGeometry, 
    1.0, cubeDeleter, enabledFlag),
yGenerationOffset(yGenerationOffset),
maxCoolingHeight(maxCoolingHeight),
minCoolingHeight(minCoolingHeight),
followEntity(followEntity),
minLaunchSpeed(minLaunchSpeed),
maxLaunchSpeed(maxLaunchSpeed),
launchMaxAngle(launchMaxAngle),
particleDuration(particleDuration),
physicalScene(physicalScene) {}

std::unique_ptr<Entity> 
SmokeFollowParticleGenerator::generateParticle(double dt) {

    if (std::shared_ptr<Entity> fEnt = followEntity.lock()) {
        if (fEnt->isAlive()) {
            
            double angle = PI + uniformRand->mapRange(-launchMaxAngle, launchMaxAngle);

            double radius = std::cos(angle);
            double y = std::sin(angle);

            double circleAngle = uniformRand->mapRange(0., 2*PI);
            double x = std::cos(circleAngle) * radius;
            double z = std::sin(circleAngle) * radius;

            Vector3 shootVector = Vector3(x, y, z);
            shootVector.normalizeFast();
            double mod = gaussianRand->mapRange(0., launchMaxAngle);
            shootVector *= mod;

            std::unique_ptr<Entity> ent = std::make_unique<Entity>(fEnt->getPos() + Vector3(0, yGenerationOffset, 0), 
                *particleGeometry, particleColor);

            ent->addComponent<TemperatureComponent>(std::make_unique<TemperatureComponent>(*ent, 0.05, 0.2, 
                maxCoolingHeight, minCoolingHeight));

            ent->addComponent<TimeDeletableComponent>(std::make_unique<TimeDeletableComponent>(particleDuration));
                
            if (gGenerateRigidbody) {
                ent->addComponent<DynamicRigidbodyComponent>(std::make_unique<DynamicRigidbodyComponent>(
                    *ent, physicalScene, shootVector, Vector3(0.), 150., 1., 1., 0.));
            }
            else {
                ent->addComponent<ParticleComponent>(std::make_unique<ParticleComponent>(shootVector, 
                    Integrator::SYMPLECTIC_EULER, 100.));
            }

            return ent;
        }
    }
    
    alive = false;
    return nullptr;    
}