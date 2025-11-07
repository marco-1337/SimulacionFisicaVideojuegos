#include "ParticleSystem.hpp"
#include "ParticleGenerator.hpp"
#include "Particle.hpp"
#include "SelfRegisteredRegistry.hpp"

ParticleSystem::ParticleSystem(): generators() {}

ParticleSystem::~ParticleSystem() {
    generators.clear();
}

// Este método está muy bien
std::weak_ptr<ParticleGenerator>
ParticleSystem::addParticleGenerator(std::unique_ptr<ParticleGenerator> generator) {
    std::shared_ptr<ParticleGenerator> addedGenerator = (std::move(generator));
    generators.push_back(addedGenerator);
    addedGenerator->getRegistry().value = this;

    return addedGenerator;
}

void
ParticleSystem::addParticle(Particle *p) {
    entities.push_back(p);
}

void
ParticleSystem::update(double dt) {

    EntityContainer::update(dt);

    for (std::list<std::shared_ptr<ParticleGenerator>>::iterator it = generators.begin(); it != generators.end();) {

        (*it)->generate(dt);
        
        if (!(*it)->isAlive()) {
            it = generators.erase(it);
        } else ++it;
    }
}