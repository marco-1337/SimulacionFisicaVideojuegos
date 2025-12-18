#pragma once

#include "ParticleGenerator.hpp"
#include "RenderUtils.hpp"
#include "GaussianRandomizer.hpp"

#include <memory>

class SmokeFollowParticleGenerator: public ParticleGenerator {
public:
    SmokeFollowParticleGenerator(std::weak_ptr<Entity> followEntity, physx::PxGeometry& particleGeometry, 
        double yGenerationOffset, double maxCoolingHeight, double minCoolingHeight, double minLaunchSpeed, 
        double maxLaunchSpeed, double launchMaxAngle, double particleDuration, double generationDuration, 
        double minTriesPerSecond, double maxTriesPerSecond, std::shared_ptr<bool> enabledFlag = nullptr);

private:
    virtual std::unique_ptr<Entity> generateParticle(double dt) override;

    std::weak_ptr<Entity> followEntity;
    
    Vector4 particleColor = Vector4(0.5);

    double  yGenerationOffset, minLaunchSpeed, maxLaunchSpeed, launchMaxAngle, particleDuration,
        maxCoolingHeight, minCoolingHeight;

    physx::PxGeometry& particleGeometry;
};