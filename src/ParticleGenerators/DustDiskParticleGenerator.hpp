#pragma once

#include "ParticleGenerator.hpp"
#include "RenderUtils.hpp"

#include <memory>

class DustDiskParticleGenerator: public ParticleGenerator {
public:
    DustDiskParticleGenerator(Vector3 pos, double radius, double minLaunchSpeed, double maxLaunchSpeed, 
        double particleMinDuration, double particleMaxDuration, Vector4 particleColor, double particleSize, 
        double generationDuration, double generationProbability, double minTriesPerSecond, 
        double maxTriesPerSecond, std::shared_ptr<bool> enabledFlag = nullptr);

private:
    virtual std::unique_ptr<Entity> generateParticle(double dt) override;

    Vector3 position; 
    Vector4 particleColor;
	physx::PxSphereGeometry particleGeometry;

    double  radius, 
            minLaunchSpeed, maxLaunchSpeed, 
            particleMinDuration, particleMaxDuration;

    std::unique_ptr<GaussianRandomizer> gaussianRand = nullptr;

    std::uniform_real_distribution<double> uniformDistribution;
};