#include "CubeAreaDeleterComponent.hpp"

#include "Entity.hpp"
#include <algorithm>

CubeAreaDeleterComponent::CubeAreaDeleterComponent(Vector3 pos, double cubeHalfHeight)
: pos(pos),
positiveCorner(pos + Vector3(cubeHalfHeight)),
negativeCorner(pos - Vector3(cubeHalfHeight)) {}

void
CubeAreaDeleterComponent::update(Entity& ent, double t) {

    Vector3 entPos = ent.getPos();

    if (entPos.x > positiveCorner.x || entPos.x < negativeCorner.x || 
        entPos.y > positiveCorner.y || entPos.y < negativeCorner.y ||
        entPos.z > positiveCorner.z || entPos.z < negativeCorner.z) { 

        ent.kill();
    }
}