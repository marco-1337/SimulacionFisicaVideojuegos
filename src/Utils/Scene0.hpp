#pragma once

#include "Scene.hpp"
#include <vector>

class RenderItem;
namespace physx { class PxTransform; }

class Scene0 : public Scene {
public:
    Scene0();
    ~Scene0();

    void enableRendering() override;

private:
    std::vector<RenderItem*> axis;
    std::vector<physx::PxTransform*> transformList;
};