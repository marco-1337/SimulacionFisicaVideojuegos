#include "GameScene.hpp"

#include "Entity.hpp"
#include "RenderUtils.hpp"
#include "EntityContainer.hpp"
#include "ParticleSystem.hpp"
#include "DustDiskParticleGenerator.hpp"

#include "Petanque.hpp"

#include <iostream>

using namespace physx;

GameScene::GameScene()
: playerAColor(1., 0., 0., 1.),
playerBColor(0., 0., 1., 1.),
dustParticleSystem(std::make_shared<ParticleSystem>()),
Scene() {

    gravityForce->registerEntityGroup(dustParticleSystem);

    double planeWidth = 0.1;
    planeExtension = 50.;

    PxBoxGeometry geometry = PxBoxGeometry(planeExtension, planeWidth, planeExtension);
	PxShape *shape = CreateShape(geometry);

    planeCentre = Vector3(0., -(planeWidth / 2.), 0);

    sceneEntities->addEntity(new Entity(planeCentre, shape, Vector4(0., 1., 0., 1.)));

    shape->release();

    double ballRadius = 1.;
    double whiteBallRadius = ballRadius / 2.;
    verticalLimit = ballRadius;

    PxSphereGeometry sphereGeometry = PxSphereGeometry(whiteBallRadius);
    shape = CreateShape(sphereGeometry);

    ballCentre = Vector3(25., whiteBallRadius, 25.);

    sceneEntities->addEntity(new Entity(ballCentre, shape, Vector4(1.)));

    shape->release();

    sphereGeometry = PxSphereGeometry(ballRadius);
    ballShape = CreateShape(sphereGeometry);


}

GameScene::~GameScene() {
    ballShape->release();
}

void 
GameScene::keyPress(unsigned char key) {

    switch(key) {
        case 'X':
            if (canShoot) {
                sceneEntities->addEntity(new Petanque(GetCamera()->getEye(), ballShape, 
                    (ATurns < BTurns) ? playerBColor : playerAColor, GetCamera()->getDir().getNormalized() * 10., 
                    Integrator::SYMPLECTIC_EULER, 1., this, verticalLimit));

                canShoot = false;

                if (ATurns < BTurns) --BTurns; 
                else --ATurns;
            }
            break;
        case 'Q':
            gravityForce->setEnabled(!gravityForce->getEnabled());
            break;
        default:
            break;
    }
}


void
GameScene::update(double dt) {
    Scene::update(dt);

    dustParticleSystem->update(dt);
}

void
GameScene::landed(Vector3 pos) {

    if (pos.x <= planeCentre.x + planeExtension && pos.z <= planeCentre.z + planeExtension ) {
        double distance = (pos - ballCentre).magnitude();

        if (minDistance < 0 || distance < minDistance) {
            minDistance = distance;
            winner = (ATurns == BTurns) ? 'B' : 'A';
        }

        dustParticleSystem->addParticleGenerator(std::make_unique<DustDiskParticleGenerator>(
        pos, 5., 0.5, 200, 500, 10., 15., 1., 5., 0.5, Vector4(1., 1., 0., 1.), 0.3));
    }

    if (ATurns > 0 || BTurns > 0) {
        canShoot = true;
    }
    else {
        std::cout << "\nHa ganado el jugador: " << winner << "\n";
    }
}

