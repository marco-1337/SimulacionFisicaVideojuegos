#include "GaussianRandomizer.hpp"

#include <algorithm>

GaussianRandomizer::GaussianRandomizer(std::shared_ptr<std::mt19937> rng, double deviation)
: rng(rng), gaussian(0., deviation) {}

double 
GaussianRandomizer::mapRange(double min, double max) {
    double mean = 0.5 * (min + max);
    return std::clamp(mean + gaussian(*rng), min, max);
}  