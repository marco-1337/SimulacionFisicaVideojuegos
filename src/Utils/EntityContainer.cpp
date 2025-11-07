#include "EntityContainer.hpp"
#include "Entity.hpp"

EntityContainer::~EntityContainer() {
    for (Entity* e : entities) {
        if (e != nullptr) {
            delete e;
        }
    }
}

void
EntityContainer::addEntity(Entity *e) { entities.push_back(e); }

const std::list<Entity*>&
EntityContainer::getEntities() { return entities; }

void
EntityContainer::update(double t) {
    for (std::list<Entity*>::iterator it = entities.begin(); it != entities.end();) {

        if (*it != nullptr) {

            (*it)->update(t);
            
            if (!(*it)->isAlive()) {
            
                Entity *aux = *it;
                it = entities.erase(it);
                delete aux;
            
            } else ++it;

        } else it = entities.erase(it);
    }
}

void
EntityContainer::enableRendering() {
    for (Entity* e : entities) if (e != nullptr) e->enableRender();
}
