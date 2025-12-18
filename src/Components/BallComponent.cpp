#include "BallComponent.hpp"

#include "Entity.hpp"
#include <algorithm>

#include "GameplayScene.hpp"

#include "DynamicRigidbodyComponent.hpp"

#include "PxRigidBody.h"

using namespace physx;

BallComponent::BallComponent(Entity& ent,  double validHeight, GameplayScene *gameplayScene)
: validHeight(validHeight),
gameplayScene(gameplayScene) {

    ent.getComponent<DynamicRigidbodyComponent>().setSleepThreshold(2.f);
}

void
BallComponent::update(Entity& ent, double t) {

    if (valid) {
        Vector3 entPos = ent.getPos();

        if (entPos.y < validHeight) { 

            gameplayScene->currentballOutOfBounds();
            valid = false;
        }
        else {
            DynamicRigidbodyComponent& dynamicComponent = ent.getComponent<DynamicRigidbodyComponent>();
            
            if (!dynamicComponent.dynamicBody->isSleeping()) {
                if (dynamicComponent.dynamicBody->getLinearVelocity().magnitude() < 1.f &&
                    dynamicComponent.dynamicBody->getAngularVelocity().magnitude() < 1.f) {

                    ent.kill();
                    gameplayScene->currentBallLanded(ent.getPos());
                }
            }
        }
    }
}

void
BallComponent::floorImpact() {
    impacted = true;
}

bool
BallComponent::isValid() { return valid; }

bool
BallComponent::hasImpacted() { return impacted; }