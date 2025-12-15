#pragma once

#include "Scene.hpp"

class Scene2: public Scene {
public:
    Scene2();

    virtual void keyPress(unsigned char key) override;
private:
    physx::PxSphereGeometry particleGeometry;
};