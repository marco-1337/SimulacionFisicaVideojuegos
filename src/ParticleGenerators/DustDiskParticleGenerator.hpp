#pragma once

#include "ParticleGenerator.hpp"
#include "RenderUtils.hpp"

#include <memory>

class DustDiskParticleGenerator: public ParticleGenerator {
public:
    DustDiskParticleGenerator(Vector3 pos, double radius, double minLaunchSpeed, double maxLaunchSpeed, 
        double particleMinDuration, double particleMaxDuration, Vector4 particleColor, 
        double generationDuration, double minTriesPerSecond, double maxTriesPerSecond, 
        physx::PxGeometry& particleGeometry, physx::PxScene *scene, 
        std::shared_ptr<CubeAreaDeleterComponent> cubeDeleter = nullptr,
        std::shared_ptr<bool> enabledFlag = nullptr);

private:
    virtual std::unique_ptr<Entity> generateParticle(double dt) override;

    Vector3 position; 
    Vector4 particleColor;

    physx::PxScene * physicalScene;

    double  radius, 
            minLaunchSpeed, maxLaunchSpeed, 
            particleMinDuration, particleMaxDuration;
};