#pragma once

#include "Killable.hpp"
#include <random>

class Entity;
class ParticleSystem;

class ParticleGenerator: public Killable {
public:

    inline ParticleGenerator(): enabled(true), random() {}
    inline ~ParticleGenerator() {}

    virtual void generate(ParticleSystem& system, double dt) = 0;
    inline bool isEnabled() { return enabled; }

protected:
    bool enabled;
    std::mt19937 random;
};