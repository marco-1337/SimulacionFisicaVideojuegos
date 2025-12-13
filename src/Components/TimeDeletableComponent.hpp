#pragma once

#include "Component.hpp"

class TimeDeletableComponent: public Component {
public:
    TimeDeletableComponent(double maxTime);

    void update(Entity& p, double t);
private:
    double currentTime;
    double maxTime;
};