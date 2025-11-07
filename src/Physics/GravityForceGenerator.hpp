#pragma once

#include "Entity.hpp"
#include <memory>
#include <list>

class EntityContainer;

class GravityForceGenerator {
public:
    GravityForceGenerator(double gravity);
    void registerEntityGroup(std::weak_ptr<EntityContainer> group);

    void applyForce();
    void setEnabled(bool val);
    bool getEnabled();

private:

    bool enabled = true;

    std::list<std::weak_ptr<EntityContainer>> entityGroups;

    Vector3 gravity;
};