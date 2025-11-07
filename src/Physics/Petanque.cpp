#include "Petanque.hpp"

#include "GameScene.hpp"

Petanque::Petanque(Vector3 position, Shape *shape, Vector4 color, Vector3 velocity, 
    Integrator integrator, double mass, GameScene *gameScene, double stopLimit) 
: Particle(position, shape, color, velocity, integrator, mass),
gameScene(gameScene),
stopLimit(stopLimit) {}

void
Petanque::update(double dt) {
    if (myTransform.p.y > stopLimit) {
        Particle::update(dt);
    }
    else if (!stopped){

        stopped = true;

        myTransform.p.y = stopLimit;
        gameScene->landed(myTransform.p);
    }
}