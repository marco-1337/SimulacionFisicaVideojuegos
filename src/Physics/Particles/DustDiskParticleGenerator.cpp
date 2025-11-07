#include "DustDiskParticleGenerator.hpp"
#include "RenderUtils.hpp"
#include "SelfRegisteredRegistry.hpp"
#include "ParticleSystem.hpp"

#include <iostream>

using namespace physx;

DustDiskParticleGenerator::DustDiskParticleGenerator(Vector3 pos, double radius, double generationProbability,
    double minTriesPerSecond, double maxTriesPerSecond, double minLaunchSpeed, double maxLaunchSpeed, 
    double particleMinDuration, double particleMaxDuration, double generationDuration, Vector4 particleColor, 
    double particleSize) 
: position(pos),
radius(radius),
minTriesPerSecond(minTriesPerSecond),
maxTriesPerSecond(maxTriesPerSecond),
generationProbability(generationProbability),
accumulatedTry(0.0),
minLaunchSpeed(minLaunchSpeed),
maxLaunchSpeed(maxLaunchSpeed),
particleMinDuration(particleMinDuration), 
particleMaxDuration(particleMaxDuration),
timeAlive(0.0),
maxTime(generationDuration),
particleColor(particleColor),
GaussianParticleGenerator() {
    PxSphereGeometry geometry = PxSphereGeometry(particleSize);
	shape = CreateShape(geometry);
}

DustDiskParticleGenerator::~DustDiskParticleGenerator() {
    shape->release();
}

void 
DustDiskParticleGenerator::generate(double dt) {
    timeAlive += dt;
    alive = timeAlive < maxTime;

    if (alive) {

        accumulatedTry += mapRange(minTriesPerSecond * dt, maxTriesPerSecond * dt);

        int generationAttempts = std::trunc(accumulatedTry);

        accumulatedTry -= generationAttempts;

        for (int i = 0; i < generationAttempts; ++i) {
            // Esto debería hacerse con una distribución uniforme, no una normal
            if (mapRange(0.0, 1.0) < generationProbability) {

                double angle = mapRange(0., PI);
                double module = mapRange(-radius, radius); 

                double absModule = std::abs(module);
                absModule = (absModule > radius / 2.) ? radius - absModule : absModule;

                double multiplier = 0.5 + (absModule / (radius/2)) * (2. - 0.5);

                Particle *p = new Particle(
                    Vector3(std::cos(angle) * module, 0., std::sin(angle) * module) + position,
                    shape,
                    particleColor,
                    Vector3(0., mapRange(minLaunchSpeed, maxLaunchSpeed) * multiplier, 0.),
                    Integrator::SYMPLECTIC_EULER,
                    0.1,
                    mapRange(particleMinDuration, particleMaxDuration)
                );

                registry->getValue().addParticle(p);
            }
        }

    }
}