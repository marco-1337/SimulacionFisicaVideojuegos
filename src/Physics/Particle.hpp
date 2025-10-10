#pragma once

#include "IntegrableEntity.hpp"

class Particle: public IntegrableEntity {
public:
    Particle(Vector3 position, Shape *shape, Vector4 color, Vector3 velocity, Vector3 acceleration, Integrator integrator, 
        double damping = 0.99, double timeToDie = 5., bool deleteable = true);
    ~Particle();

    void update(double t) override;
    bool needToDelete() override;

protected:
    bool deleteable;
    double timeToDie; 
    double aliveTime;
};