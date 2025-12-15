#pragma once

#include "Killable.hpp"
#include "FlaggedActivable.hpp"

#include "GaussianRandomizer.hpp"
#include "UniformRandomizer.hpp"

#include <random>
#include <memory>

class Entity;
class ParticleSystem;

class ParticleGenerator: public Killable, public FlaggedActivable  {
public:
    ParticleGenerator(double generationDuration, double generationProbability, double minTriesPerSecond, 
        double maxTriesPerSecond, std::shared_ptr<bool> enabled = nullptr);
    
    void generate(ParticleSystem& system, double dt);

protected:

    virtual std::unique_ptr<Entity> generateParticle(double dt) = 0;

    std::shared_ptr<std::mt19937> random;

    std::unique_ptr<GaussianRandomizer> gaussianRand = nullptr;
    std::unique_ptr<UniformRandomizer> uniformRand = nullptr;

    double generationDuration, timeAlive, generationProbability, 
        minTriesPerSecond, maxTriesPerSecond, accumulatedTry;
};