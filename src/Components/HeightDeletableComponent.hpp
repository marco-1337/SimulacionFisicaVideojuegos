#pragma once

#include "Component.hpp"

class HeightDeletableComponent: public Component {
public:
    HeightDeletableComponent(double height, bool under = true);

    void update(Entity& p, double t);
private:
    double height;
    bool under;
};