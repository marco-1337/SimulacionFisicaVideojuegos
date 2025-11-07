#pragma once

#include <list>
#include <memory>
#include "EntityContainer.hpp"

class Particle;
class ParticleGenerator;

class ParticleSystem: public EntityContainer {
public:

    ParticleSystem();
    ~ParticleSystem();

    /// @brief Añade el generador al sistema, haciendolo propietario del mismo, y registrando el sistema en el generador
    /// @param generator 
    /// @return Referencia débil para poder llamar al generador desde fuera sin dar propiedad
    std::weak_ptr<ParticleGenerator> addParticleGenerator(std::unique_ptr<ParticleGenerator> generator);
    virtual void update(double dt) override;

    void addParticle(Particle *p);

private:
    std::list<std::shared_ptr<ParticleGenerator>> generators;
};