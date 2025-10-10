#include "Scene.hpp"

#include "Entity.hpp"

Scene::Scene(): entities() {}

Scene::~Scene() {
    for (Entity* e : entities) {
        if (e != nullptr) {
            delete e;
        }
    }
}

void
Scene::update(double t) {
    for (std::list<Entity*>::iterator it = entities.begin(); it != entities.end();) {

        if (*it != nullptr) {

            (*it)->update(t);
            
            if ((*it)->needToDelete()) {
            
                Entity *aux = *it;
                it = entities.erase(it);
                delete aux;
            
            } else ++it;

        } else it = entities.erase(it);
    }
}

void
Scene::keyPress(unsigned char key) { }

void
Scene::enableRendering() {
    for (Entity* e : entities) if (e != nullptr) e->enableRender();
}