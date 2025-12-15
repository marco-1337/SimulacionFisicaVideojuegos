#pragma once

#include <random>
#include <memory>

class GaussianRandomizer {
public:
    GaussianRandomizer(std::shared_ptr<std::mt19937> rng, double deviation = 0.3);

    double mapRange(double min, double max);

protected:
    std::normal_distribution<double> gaussian;

    std::shared_ptr<std::mt19937> rng = nullptr;
};