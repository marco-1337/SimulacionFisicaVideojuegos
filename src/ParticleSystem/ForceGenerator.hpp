#pragma once

#include <unordered_set>

#include <memory>

#include "Killable.hpp"
#include "FlaggedActivable.hpp"
#include "Entity.hpp"

class ForceGenerator: public Killable, public FlaggedActivable {
public:
    inline ForceGenerator( std::shared_ptr<bool> enabledFlag = std::make_shared<bool>(true))
        : FlaggedActivable(enabledFlag) {}

    virtual void tryAddForce(Entity& ent, double dt) = 0;

    void setEnabled(bool e) { *enabledFlag = e; }
};