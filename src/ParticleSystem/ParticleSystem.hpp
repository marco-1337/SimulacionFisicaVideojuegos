#pragma once

#include <list>
#include <memory>
#include <unordered_set>

#include "Killable.hpp"
#include "KillableList.hpp"
#include "Entity.hpp"
#include "ParticleGenerator.hpp"
#include "ForceGenerator.hpp"

class ParticleSystem: public Killable{
public:

    ParticleSystem(size_t maxParticles);

    /// @brief Añade el generador al sistema, haciendolo propietario del mismo, 
    ///         y registrando el sistema en el generador
    /// @param generator 
    /// @return Referencia débil para poder llamar al generador desde fuera sin dar propiedad
    std::weak_ptr<ParticleGenerator> addParticleGenerator(std::unique_ptr<ParticleGenerator> generator);
    void registerForceGenerator(std::shared_ptr<ForceGenerator> generator);
    void addParticle(std::unique_ptr<Entity> ent);

    void update(double dt);
    void enabledRender();

private:
    KillableList<Entity> particleList;
    KillableList<ParticleGenerator> particleGenerators;
    std::unordered_set<std::shared_ptr<ForceGenerator>> forceGeneratorsRegistry;
};