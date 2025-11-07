#pragma once

#include <list>
class Entity;

class EntityContainer {
public:
    EntityContainer() {}
    virtual ~EntityContainer();

    void addEntity(Entity *e);
    const std::list<Entity*>& getEntities();

    virtual void update(double t);
    virtual void enableRendering();
    
protected:
    std::list<Entity*> entities;
};