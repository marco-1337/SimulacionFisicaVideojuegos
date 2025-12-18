#include "Scene2.hpp"

#include <memory>
#include <iostream>

#include "RenderUtils.hpp"
#include "ParticleComponent.hpp"
#include "ProjectileParticleComponent.hpp"

#include "StaticRigidbodyComponent.hpp"
#include "DynamicRigidbodyComponent.hpp"

#include "SmokeFollowParticleGenerator.hpp"
#include "ThermalLiftForceGenerator.hpp"

#include "GravityForceGenerator.hpp"
#include "BuoyancyForceGenerator.hpp"

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

    PxBoxGeometry box = PxBoxGeometry(30., 50., 30.);
    ent = std::make_unique<Entity>(Vector3(0., -60., 0.), box, Vector4(1., 0.5, 1., 1.));
    ent->addComponent<StaticRigidbodyComponent>(std::make_unique<StaticRigidbodyComponent>(*ent, myPhysxScene));
    sceneEntities.addObject(std::move(ent));
    ent = nullptr;

    box = PxBoxGeometry(200., 48., 200.);
    ent = std::make_unique<Entity>(Vector3(0., -60., 0.), box, Vector4(0.6, 0.8, 1., 0.6));
    sceneEntities.addObject(std::move(ent));

    particleSystems.push_back(std::make_shared<ParticleSystem>());
    smokeSystem = particleSystems.back();

    gravityForce = std::make_shared<GravityForceGenerator>(GRAVITY_FORCE);
    buoyancyForce = std::make_shared<BuoyancyForceGenerator>(-12);

    sceneForceGeneratorsRegistry.insert(gravityForce);
    sceneForceGeneratorsRegistry.insert(buoyancyForce);

    smokeSystem->registerForceGenerator(gravityForce);
    smokeSystem->registerForceGenerator(std::make_shared<ThermalLiftForceGenerator>(3.));
}

void 
Scene2::keyPress(unsigned char key) {
    switch (key) {
        case 'P': {
            std::unique_ptr<Entity> particle = std::make_unique<Entity>(Vector3(0.), 
                particleGeometry, Vector4(1., 1., 0., 1.));

            particle->addComponent<ParticleComponent>(
                std::make_shared<ParticleComponent>(Vector3(1., 2., -1.).getNormalized() * 3.5, 
                Integrator::SYMPLECTIC_EULER , 100.0));

            sceneEntities.addObject(std::move(particle));
        }

        break;
        
        case 'O': {
            std::unique_ptr<Entity> particle = std::make_unique<Entity>(Vector3(0.), 
                particleGeometry, Vector4(0., 1., 1., 1.));

            particle->addComponent<ParticleComponent>(
                std::make_shared<ProjectileParticleComponent>(Vector3(1., 2., -1.).getNormalized(), 
                Integrator::SYMPLECTIC_EULER , 100.0, 3.5, 1.));

            sceneEntities.addObject(std::move(particle));
        }
        break;

        case 'I': {
            std::unique_ptr<Entity> particle = std::make_unique<Entity>(Vector3(0.), 
                particleGeometry, Vector4(0., 1., 1., 1.));

            particle->addComponent<ParticleComponent>(
                std::make_shared<ProjectileParticleComponent>(Vector3(1., 2., -1.).getNormalized(), 
                Integrator::SYMPLECTIC_EULER , 100.0, 3.5, 7.));

            sceneEntities.addObject(std::move(particle));
        }
        break;

        case 'V': {

            std::unique_ptr<Entity> particle = std::make_unique<Entity>(Vector3(0.), 
                particleGeometry, Vector4(0., 1., 1., 1.));

            particle->addComponent<DynamicRigidbodyComponent>(
                std::make_shared<DynamicRigidbodyComponent>(*particle, myPhysxScene, 
                    Vector3(0., 2., 0.).getNormalized() * 3.5, Vector3(0., 0., 1.), 100.0));

            sceneEntities.addObject(std::move(particle));
        }
        break;

        case 'B': {
            std::unique_ptr<Entity> particle = std::make_unique<Entity>(Vector3(0.), 
                particleGeometry, Vector4(1., 0.5, 0.2, 1.));

            particle->addComponent<DynamicRigidbodyComponent>(
                std::make_shared<DynamicRigidbodyComponent>(*particle, myPhysxScene,
                    Vector3(-20., 20., -20.).getNormalized() * 3.5, Vector3(0., 0., 1.), 100.0));

            std::weak_ptr<Entity> objReference = sceneEntities.addObject(std::move(particle));

            smokeSystem->addParticleGenerator(std::make_unique<SmokeFollowParticleGenerator>(
                    objReference, // entidad que va a seguir
                    2., // offset vertical para generar la partícula
                    50., // altura donde las partículas se enfrian mas rápido
                    20., // altura donde las partículas se enfrían mas lento
                    10., // velocidad inicial mínima
                    20., // velocidad inicial máxima
                    PI/2., // angulo máximo de lanzamiento
                    7., // tiempo de vida de cada partícula
                    5., // tiempo de vida del generador
                    50., // generaciones mínimas por segundo
                    150., // generaciones máximas por segundo
                    particleGeometry,
                    myPhysxScene));
        }
        break;
	}
}