#pragma once

#include "Particle.hpp"
#include "GaussianParticleGenerator.hpp"

namespace physx {
    class PxShape;
}

class DustDiskParticleGenerator: public GaussianParticleGenerator {
public:
    DustDiskParticleGenerator(Vector3 pos, double radius, double generationProbability, double minTriesPerSecond, 
        double maxTriesPerSecond, double minLaunchSpeed, double maxLaunchSpeed, double particleMinDuration, 
        double particleMaxDuration, double generationDuration, Vector4 particleColor, double particleSize);
    ~DustDiskParticleGenerator();

    void generate(double dt) override;
    
private:
    Vector3 position; 
    Vector4 particleColor;
	physx::PxShape *shape;

    double  timeAlive, maxTime,
            radius, 
            generationProbability, 
            minTriesPerSecond, maxTriesPerSecond, accumulatedTry,
            minLaunchSpeed, maxLaunchSpeed, 
            particleMinDuration, particleMaxDuration;

    
};