#include "ParticleGenerator.hpp"

#include "ParticleSystem.hpp"

ParticleGenerator::ParticleGenerator(double generationDuration, double generationProbability, double minTriesPerSecond, 
    double maxTriesPerSecond, std::shared_ptr<bool> enabled)
: FlaggedActivable(enabled), 
random(std::make_shared<std::mt19937>()),
generationDuration(generationDuration),
timeAlive(0.),
accumulatedTry(0.),
generationProbability(generationProbability),
minTriesPerSecond(minTriesPerSecond),
maxTriesPerSecond(maxTriesPerSecond) {
    gaussianRand = std::make_unique<GaussianRandomizer>(random);
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
        if (uniformRand->mapRange(0., 1.) < generationProbability) {
            system.addParticle(generateParticle(dt));
        }
    }
}