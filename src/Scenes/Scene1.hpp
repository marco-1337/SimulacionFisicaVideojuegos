#pragma once

#include "Scene.hpp"

class Scene1: public Scene {
public:
    Scene1();
    virtual void keyPress(unsigned char key) override {}
};