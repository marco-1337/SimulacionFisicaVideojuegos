#pragma once

#include "Particle.hpp"

class GameScene;

class Petanque: public Particle {
public:
    Petanque(Vector3 position, Shape *shape, Vector4 color, Vector3 velocity, 
        Integrator integrator, double mass, GameScene *gameScene, double stopLimit);

    void update(double dt) override;
private:

    bool stopped = false;

    double stopLimit;

    GameScene *gameScene;
};