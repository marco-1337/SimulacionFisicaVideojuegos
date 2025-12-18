#include "BolicheComponent.hpp"

#include "Entity.hpp"
#include <algorithm>

#include "GameplayScene.hpp"

BolicheComponent::BolicheComponent(Vector3 pos, double cubeHalfHeight, double heightStop, GameplayScene *gameplayScene)
: pos(pos),
positiveCorner(pos + Vector3(cubeHalfHeight)),
negativeCorner(pos - Vector3(cubeHalfHeight)),
gameplayScene(gameplayScene),
heightStop(heightStop){}

void
BolicheComponent::update(Entity& ent, double t) {

    if (ent.isAlive()) {
        Vector3 entPos = ent.getPos();

        if (entPos.x > positiveCorner.x || entPos.x < negativeCorner.x || 
            entPos.z > positiveCorner.z || entPos.z < negativeCorner.z) {

            if (entPos.y < heightStop) {
                ent.kill();
                gameplayScene->bolicheOutOfBounds();
            }
        }
        else if (entPos.y <= heightStop) {
            ent.kill();
            gameplayScene->bolicheLanded(entPos.x, entPos.z);
        }
    } 
}