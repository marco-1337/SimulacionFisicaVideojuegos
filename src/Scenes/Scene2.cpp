#include "Scene2.hpp"

#include <memory>
#include <iostream>

#include "RenderUtils.hpp"
#include "ParticleComponent.hpp"
#include "ProjectileParticleComponent.hpp"

#include "StaticRigidbodyComponent.hpp"
#include "DynamicRigidbodyComponent.hpp"

#include "GravityForceGenerator.hpp"

#include "consts.hpp"

using namespace physx;

Scene2::Scene2() {

    particleGeometry = PxSphereGeometry(0.4f);

    std::unique_ptr<Entity> ent = std::make_unique<Entity>(Vector3(0.), particleGeometry, Vector4(1.));
    sceneEntities.addObject(std::move(ent));

    ent = std::make_unique<Entity>(Vector3(10., 0., 0.), particleGeometry, Vector4(1., 0., 0., 1.));
    sceneEntities.addObject(std::move(ent));
    
    ent = std::make_unique<Entity>(Vector3(0., 10., 0.), particleGeometry, Vector4(0., 1., 0., 1.));
    sceneEntities.addObject(std::move(ent));
    
    ent = std::make_unique<Entity>(Vector3(0., 0., 10.), particleGeometry, Vector4(0., 0., 1., 1.));
    sceneEntities.addObject(std::move(ent));

    sceneForceGeneratorsRegistry.insert(std::make_shared<GravityForceGenerator>(GRAVITY_FORCE));

    PxBoxGeometry box = PxBoxGeometry(30., 0.1, 30.);
    ent = std::make_unique<Entity>(Vector3(0., -10., 0.), box, Vector4(0.5, 0., 0.5, 1.));
    ent->addComponent<StaticRigidbodyComponent>(std::make_unique<StaticRigidbodyComponent>(*ent, myPhysxScene));
    sceneEntities.addObject(std::move(ent));
}

void 
Scene2::keyPress(unsigned char key) {
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

        case 'V': {

            particleGeometry = PxSphereGeometry(1.f);

            std::unique_ptr<Entity> particle = std::make_unique<Entity>(Vector3(0.), 
                particleGeometry, Vector4(0., 1., 1., 1.));

            particle->addComponent<DynamicRigidbodyComponent>(
                std::make_shared<DynamicRigidbodyComponent>(*particle, myPhysxScene, 
                    Vector3(0., 2., 0.).getNormalized() * 3.5, Vector3(0., 0., 1.), 1.0));

            sceneEntities.addObject(std::move(particle));
        }
            
        break;
	}
}