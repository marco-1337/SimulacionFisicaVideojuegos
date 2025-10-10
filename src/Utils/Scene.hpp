#pragma once

#include <list>

class Entity;

class Scene {
public:
    Scene();
    virtual ~Scene() = 0;

    virtual void update(double t);
    virtual void keyPress(unsigned char key);
    virtual void enableRendering();

protected:
    std::list<Entity*> entities;
};