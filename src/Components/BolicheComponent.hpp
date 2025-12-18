#pragma once

#include "Component.hpp"

#include "core.hpp"

class GameplayScene;

class BolicheComponent: public Component {
public:
    BolicheComponent(Vector3 pos, double cubeHalfHeight, double heightStop, GameplayScene *gameplayScene);

    void update(Entity& p, double t);
private:
    Vector3 pos, positiveCorner, negativeCorner;

    double heightStop;

    GameplayScene *gameplayScene = nullptr;
};