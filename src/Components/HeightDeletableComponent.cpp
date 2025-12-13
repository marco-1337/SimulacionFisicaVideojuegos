#include "HeightDeletableComponent.hpp"

#include "Entity.hpp"
#include <algorithm>

HeightDeletableComponent::HeightDeletableComponent(double height, bool under)
: height(height),
under(under) {}

void
HeightDeletableComponent::update(Entity& ent, double t) {
    if (under) { 
        if (ent.getPos().y <= height) ent.kill();
    }
    else {
        if (ent.getPos().y >= height) ent.kill();
    }
}