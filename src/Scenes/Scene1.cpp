#include "Scene1.hpp"

#include <memory>
#include <iostream>

#include "RenderUtils.hpp"
#include "ParticleComponent.hpp"
#include "ProjectileParticleComponent.hpp"

#include "GravityForceGenerator.hpp"
#include "DustDiskParticleGenerator.hpp"

#include "consts.hpp"

using namespace physx;

Scene1::Scene1() {

    particleGeometry = PxSphereGeometry(0.4f);

    std::unique_ptr<Entity> axisElem = std::make_unique<Entity>(Vector3(0.), particleGeometry, Vector4(1.));
    sceneEntities.addObject(std::move(axisElem));

    axisElem = std::make_unique<Entity>(Vector3(10., 0., 0.), particleGeometry, Vector4(1., 0., 0., 1.));
    sceneEntities.addObject(std::move(axisElem));

    axisElem = std::make_unique<Entity>(Vector3(0., 10., 0.), particleGeometry, Vector4(0., 1., 0., 1.));
    sceneEntities.addObject(std::move(axisElem));
    
    axisElem = std::make_unique<Entity>(Vector3(0., 0., 10.), particleGeometry, Vector4(0., 0., 1., 1.));
    sceneEntities.addObject(std::move(axisElem));

    gravityForce = std::make_shared<GravityForceGenerator>(GRAVITY_FORCE);

    sceneForceGeneratorsRegistry.insert(gravityForce);

    particleSystems.push_back(ParticleSystem());
    dustSystem = &(particleSystems.back());
    dustSystem->registerForceGenerator(gravityForce);
}

void 
Scene1::keyPress(unsigned char key) {
    switch (key) {
        case 'P': {
            std::unique_ptr<Entity> particle = std::make_unique<Entity>(Vector3(0.), 
                particleGeometry, Vector4(1., 1., 0., 1.));

            particle->addComponent<ParticleComponent>(
                std::make_shared<ParticleComponent>(Vector3(1., 2., -1.).getNormalized() * 3.5, 
                Integrator::SYMPLECTIC_EULER , 1.0));

            sceneEntities.addObject(std::move(particle));
        }
        break;
        
        case 'O': {
            std::unique_ptr<Entity> particle = std::make_unique<Entity>(Vector3(0.), 
                particleGeometry, Vector4(0., 1., 1., 1.));

            particle->addComponent<ParticleComponent>(
                std::make_shared<ProjectileParticleComponent>(Vector3(1., 2., -1.).getNormalized(), 
                Integrator::SYMPLECTIC_EULER , 1.0, 3.5, 1.));

            sceneEntities.addObject(std::move(particle));
        }
            
        break;

        case 'I': {
            std::unique_ptr<Entity> particle = std::make_unique<Entity>(Vector3(0.), 
                particleGeometry, Vector4(0., 1., 1., 1.));

            particle->addComponent<ParticleComponent>(
                std::make_shared<ProjectileParticleComponent>(Vector3(1., 2., -1.).getNormalized(), 
                Integrator::SYMPLECTIC_EULER , 1.0, 3.5, 7.));

            sceneEntities.addObject(std::move(particle));
        }
            
        break;

        case 'J': {
            dustSystem->addParticleGenerator(
                std::make_unique<DustDiskParticleGenerator>(
                    Vector3(0.), 5., 0.5, 500, 1000, 10., 15., 1., 5., 1., Vector4(1., 1., 0., 1.), 0.3)
            );
        }
	} 
}