#include "Scene2.hpp"
#include "Entity.hpp"
#include "ParticleSystem.hpp"
#include "RenderUtils.hpp"
#include "EntityContainer.hpp"
#include "DustDiskParticleGenerator.hpp"

using namespace physx;

Scene2::Scene2():
Scene(),
pSystem(std::make_shared<ParticleSystem>()) {

    gravityForce->registerEntityGroup(pSystem);

    PxSphereGeometry geometry = PxSphereGeometry(0.5f);
	PxShape *particleShape = CreateShape(geometry);

    sceneEntities->addEntity(new Entity(Vector3(0., 0., 0), particleShape, Vector4(1.)));

    sceneEntities->addEntity(new Entity(Vector3(10., 0., 0), particleShape, Vector4(1., 0., 0., 1.)));
    sceneEntities->addEntity(new Entity(Vector3(5., 0., 0), particleShape, Vector4(1., 0., 0., 1.)));

    sceneEntities->addEntity(new Entity(Vector3(0., 10., 0), particleShape, Vector4(0., 1., 0., 1.)));
    sceneEntities->addEntity(new Entity(Vector3(0., 5., 0), particleShape, Vector4(0., 1., 0., 1.)));

    sceneEntities->addEntity(new Entity(Vector3(0., 0., 10.), particleShape, Vector4(0., 0., 1., 1.)));
    sceneEntities->addEntity(new Entity(Vector3(0., 0., 5.), particleShape, Vector4(0., 0., 1., 1.)));
}

Scene2::~Scene2() {}

void 
Scene2::keyPress(unsigned char key) {
    switch(key) {
        case 'G':
            pSystem->addParticleGenerator(std::make_unique<DustDiskParticleGenerator>(
                Vector3(0.), 5., 0.5, 500, 1000, 10., 15., 1., 5., 0.5, Vector4(1., 1., 0., 1.), 0.3));
            break;
    }
}

void
Scene2::update(double dt) {
    Scene::update(dt);

    pSystem->update(dt);
}