#include "TimeDeletableComponent.hpp"

#include "Entity.hpp"

#include <algorithm>

TimeDeletableComponent::TimeDeletableComponent(double maxTime)
: currentTime(0.) {
    this->maxTime = std::max(maxTime, 0.); 
}

void
TimeDeletableComponent::update(Entity& ent, double t) {
    currentTime += t;
    if (currentTime >= maxTime) { ent.kill(); }
}