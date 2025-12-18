#include "ParticleGenerator.hpp"

#include "ParticleSystem.hpp"

ParticleGenerator::ParticleGenerator(double generationDuration, double minTriesPerSecond, double maxTriesPerSecond, 
    physx::PxGeometry& particleGeometry, double gaussianDeviation, 
    std::shared_ptr<CubeAreaDeleterComponent> cubeDeleter, std::shared_ptr<bool> enabled)

: FlaggedActivable(enabled), 
random(std::make_shared<std::mt19937>()),
generationDuration(generationDuration),
timeAlive(0.),
accumulatedTry(0.),
minTriesPerSecond(minTriesPerSecond),
maxTriesPerSecond(maxTriesPerSecond),
particleGeometryHolder(particleGeometry),
cubeDeleter(cubeDeleter) {

    this->particleGeometry = &(particleGeometryHolder.any());

    gaussianRand = std::make_unique<GaussianRandomizer>(random, gaussianDeviation);
    uniformRand = std::make_unique<UniformRandomizer>(random);
}

void 
ParticleGenerator::generate(ParticleSystem& system, double dt) {

    timeAlive += dt;
    alive = timeAlive < generationDuration;
    accumulatedTry += gaussianRand->mapRange(minTriesPerSecond * dt, maxTriesPerSecond * dt);
    int generationAttempts = std::trunc(accumulatedTry);
    accumulatedTry -= generationAttempts;
    
    for (int i = 0; i < generationAttempts; ++i) {
        if (std::unique_ptr<Entity> part = generateParticle(dt)) {

            if (cubeDeleter) part->addComponent<CubeAreaDeleterComponent>(cubeDeleter);

            system.addParticle(std::move(part));
        }
        else i = generationAttempts;
    }
}