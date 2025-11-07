#pragma once

#include <random>

class Particle;
class ParticleSystem;

template <typename T>
class SelfRegisteredRegistry;

class ParticleGenerator {
public:

    ParticleGenerator();
    ~ParticleGenerator();

    virtual void generate(double dt) = 0;

    inline bool isEnabled() { return enabled; }
    inline bool isAlive() { return alive; }

    inline SelfRegisteredRegistry<ParticleSystem>& getRegistry() { return *registry; }

protected:
    bool enabled;
    bool alive;

    std::mt19937 random;

    SelfRegisteredRegistry<ParticleSystem> *registry;
};