#pragma once

#include "ParticleGenerator.hpp"
#include "RenderUtils.hpp"
#include "GaussianRandomizer.hpp"

#include <memory>

class SmokeFollowParticleGenerator: public ParticleGenerator {
public:
    SmokeFollowParticleGenerator(std::weak_ptr<Entity> followEntity, double yGenerationOffset, double maxCoolingHeight, 
        double minCoolingHeight, double minLaunchSpeed, double maxLaunchSpeed, double launchMaxAngle, 
        double particleDuration, double generationDuration, double minTriesPerSecond, double maxTriesPerSecond, 
        physx::PxGeometry& particleGeometry, physx::PxScene *physicalScene,
        std::shared_ptr<CubeAreaDeleterComponent> cubeDeleter = nullptr,
        std::shared_ptr<bool> enabledFlag = nullptr);

private:
    virtual std::unique_ptr<Entity> generateParticle(double dt) override;

    std::weak_ptr<Entity> followEntity;
    
    Vector4 particleColor = Vector4(0.5);

    physx::PxScene * physicalScene;

    double  yGenerationOffset, minLaunchSpeed, maxLaunchSpeed, launchMaxAngle, particleDuration,
        maxCoolingHeight, minCoolingHeight;
};