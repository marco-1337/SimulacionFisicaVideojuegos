#pragma once

#include "Component.hpp"

#include "core.hpp"

class GameplayScene;

class BallComponent: public Component {
public:
    BallComponent(Entity& ent, double validHeight, GameplayScene *gameplayScene);
    void update(Entity& p, double t);

    bool isValid();
    void floorImpact();
    bool hasImpacted();

private:
    double validHeight;

    bool valid = true;

    bool impacted = false;

    GameplayScene *gameplayScene = nullptr;
};