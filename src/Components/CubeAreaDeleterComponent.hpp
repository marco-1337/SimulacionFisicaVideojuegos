#pragma once

#include "Component.hpp"

#include "core.hpp"

class CubeAreaDeleterComponent: public Component {
public:
    CubeAreaDeleterComponent(Vector3 pos, double cubeHalfHeight);

    void update(Entity& p, double t);
private:
    Vector3 pos, positiveCorner, negativeCorner;
};