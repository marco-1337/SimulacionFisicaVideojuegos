#pragma once

#include <list>
#include <memory>
#include <unordered_set>

#include "KillableList.hpp"
#include "Entity.hpp"
#include "ParticleGenerator.hpp"
#include "ForceGenerator.hpp"

class ParticleSystem {
public:

    ParticleSystem();

    std::weak_ptr<ParticleGenerator> addParticleGenerator(std::unique_ptr<ParticleGenerator> generator);
    void registerForceGenerator(std::shared_ptr<ForceGenerator> generator);
    void addParticle(std::unique_ptr<Entity> ent);
    
    void update(double dt);
    void enableRender();

private:
    KillableList<Entity> particleList;
    KillableList<ParticleGenerator> particleGenerators;
    std::unordered_set<std::shared_ptr<ForceGenerator>> forceGeneratorsRegistry;
};