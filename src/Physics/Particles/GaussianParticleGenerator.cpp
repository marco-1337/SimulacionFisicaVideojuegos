#include "GaussianParticleGenerator.hpp"

// Devuelve un numero aleatorio entre min y max en base a la distribucion normal (truncado)
double
GaussianParticleGenerator::mapRange(double min, double max) {
    double prob = gaussian(random);

    prob = std::clamp(prob, -1., 1.);

    return min + ((prob + 1.0) / 2.0) * (max - min);
}