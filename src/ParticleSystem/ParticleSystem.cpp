#include "ParticleSystem.hpp"

#include "Entity.hpp"

#include "ParticleGenerator.hpp"
#include "ForceGenerator.hpp"

#include <algorithm>
#include <functional>

ParticleSystem::ParticleSystem(size_t maxParticles)
: particleList(),
particleGenerators(),
forceGeneratorsRegistry() {}

void
ParticleSystem::addParticle(std::unique_ptr<Entity> ent) {

    if (ent->hasComponent<ParticleComponent>()) {
        particleList.addObject(std::move(ent));
    }
}

std::weak_ptr<ParticleGenerator>
ParticleSystem::addParticleGenerator(std::unique_ptr<ParticleGenerator> generator) {
    return particleGenerators.addObject(std::move(generator));
}

void 
ParticleSystem::registerForceGenerator(std::shared_ptr<ForceGenerator> generator) {
    forceGeneratorsRegistry.insert(generator);
}

void
ParticleSystem::update(double dt) {

    particleGenerators.foreachAlive( [this, dt] (ParticleGenerator &generator) {
        generator.generate(*this, dt);
    });

    particleList.foreachAlive( [this, dt] (Entity &particle) {

        for (auto forceGen : this->forceGeneratorsRegistry) {
            if (forceGen->isAlive() && forceGen->isEnabled()) forceGen->tryAddForce(particle, dt);
        } 

        particle.update(dt);
    });
    
    for (auto it = forceGeneratorsRegistry.begin(); it != forceGeneratorsRegistry.end(); ) {
        if (!(*it)->isAlive()) it = forceGeneratorsRegistry.erase(it);
        else ++it;
    }
}

void
ParticleSystem::enabledRender() {
    particleList.foreachAlive( [] (Entity &particle) { particle.enableRender(); } );
}