#include "ParticleGenerator.hpp"
#include "SelfRegisteredRegistry.hpp"

ParticleGenerator::ParticleGenerator()
: enabled(true),
alive(true),
random(),
registry(new SelfRegisteredRegistry<ParticleSystem>()) 
{}

ParticleGenerator::~ParticleGenerator() {
    delete registry;
}