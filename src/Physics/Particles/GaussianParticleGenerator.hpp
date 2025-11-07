#pragma once

#include "ParticleGenerator.hpp"

class GaussianParticleGenerator: public ParticleGenerator {
public:

    inline GaussianParticleGenerator(): gaussian(0., 0.388), ParticleGenerator() {}

protected:

    double mapRange(double min, double max);

    std::normal_distribution<double> gaussian;
};