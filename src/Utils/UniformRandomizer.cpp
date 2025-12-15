#include "UniformRandomizer.hpp"

#include <algorithm>

UniformRandomizer::UniformRandomizer(std::shared_ptr<std::mt19937> rng)
: rng(rng), uniform(0., 1.) {}

double 
UniformRandomizer::mapRange(double min, double max) {
    return min + (uniform(*rng) * std::max(max - min, 0.));
}  