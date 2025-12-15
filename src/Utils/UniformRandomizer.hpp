#pragma once

#include <random>
#include <memory>

class UniformRandomizer {
public:
    UniformRandomizer(std::shared_ptr<std::mt19937> rng);
    double mapRange(double min, double max);

protected:
    std::uniform_real_distribution<double> uniform;

    std::shared_ptr<std::mt19937> rng = nullptr;
};