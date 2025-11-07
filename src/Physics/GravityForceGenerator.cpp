#include "GravityForceGenerator.hpp"
#include "EntityContainer.hpp"
#include "Entity.hpp"

GravityForceGenerator::GravityForceGenerator(double gravity)
: gravity(0., gravity, 0.),
entityGroups() {}

void 
GravityForceGenerator::registerEntityGroup(std::weak_ptr<EntityContainer> group) {
    entityGroups.push_back(group);
}

void
GravityForceGenerator::applyForce() {

    if (enabled) {
        for (std::list<std::weak_ptr<EntityContainer>>::iterator it = entityGroups.begin(); it != entityGroups.end();) {
            if (std::shared_ptr<EntityContainer> group = it->lock()) {

                const std::list<Entity*>& entitiesInGroup = group->getEntities();

                for (Entity *e : entitiesInGroup) {
                    e->addForce(e->getMass() * gravity);
                }

                ++it;
            }
            else {
                it = entityGroups.erase(it);
            }
        }
    }
}

void
GravityForceGenerator::setEnabled(bool val) { enabled = val; }

bool
GravityForceGenerator::getEnabled() { return enabled; }