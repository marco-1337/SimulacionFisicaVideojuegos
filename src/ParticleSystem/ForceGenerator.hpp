#pragma once

#include <unordered_set>

#include "Killable.hpp"
#include "Entity.hpp"

class ForceGenerator: public Killable {
public:
    virtual void tryAddForce(Entity& ent, double dt) = 0;
    inline bool isEnabled() { return enabled; }

protected:
    bool enabled;
};