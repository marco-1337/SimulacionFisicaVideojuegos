#pragma once

class Entity;

class Component {
public:
    inline Component() {}
    virtual void update(Entity& ent,  double t) {};
};