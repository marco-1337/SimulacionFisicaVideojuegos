#include "GameplayScene.hpp"

#include <memory>
#include <iostream>

#include "RenderUtils.hpp"
#include "ParticleComponent.hpp"
#include "ProjectileParticleComponent.hpp"
#include "BolicheComponent.hpp"
#include "BallComponent.hpp"
#include "StaticRigidbodyComponent.hpp"
#include "DynamicRigidbodyComponent.hpp"
#include "CubeAreaDeleterComponent.hpp"
#include "FloorComponent.hpp"

#include "SmokeFollowParticleGenerator.hpp"
#include "ThermalLiftForceGenerator.hpp"
#include "DustDiskParticleGenerator.hpp"
#include "ExplosionForceGenerator.hpp"

#include "GravityForceGenerator.hpp"
#include "BuoyancyForceGenerator.hpp"

#include "consts.hpp"

#include <iostream>

#include <limits>

using namespace physx;

GameplayScene::GameplayScene()
: balls(),
minDistanceRed(std::numeric_limits<float>().infinity()),
minDistanceBlue(std::numeric_limits<float>().infinity()),
whiteBallPos(),
canShoot(true),
shootWhite(false),
blueTurn(true),
nRounds(0),
maxRounds(3),
fieldRadius(50.),
particleMass(100.),
ballMass(2000.) {

    particleGeometryHolder = PxBoxGeometry(0.1, 0.1, 0.1);
    bolicheGeometry = PxSphereGeometry(0.5);
    ballGeometry = PxSphereGeometry(1.);

    std::unique_ptr<Entity> ent;

    // Suelo

    PxBoxGeometry box = PxBoxGeometry(fieldRadius, fieldRadius, fieldRadius);
    ent = std::make_unique<Entity>(Vector3(0., -10. - fieldRadius, 0.), box, Vector4(0.25, 1.0, 0.25, 1.));
    ent->addComponent<StaticRigidbodyComponent>(std::make_unique<StaticRigidbodyComponent>(*ent, myPhysxScene));
    ent->addComponent<FloorComponent>(std::make_unique<FloorComponent>());
    sceneEntities.addObject(std::move(ent));
    ent = nullptr;

    // Mar

    box = PxBoxGeometry(fieldRadius * 10., fieldRadius - 3., fieldRadius * 10.);
    ent = std::make_unique<Entity>(Vector3(0., -10. - fieldRadius, 0.), box, Vector4(0.6, 0.8, 1., 0.6));
    sceneEntities.addObject(std::move(ent));

    // Componente de destruccion por area de cubo compartido

    deleteAreaComponent = std::make_shared<CubeAreaDeleterComponent>(Vector3(0., -10., 0.), fieldRadius * 3.);

    // Generadores de fuerza

    gravityForce = std::make_shared<GravityForceGenerator>(GRAVITY_FORCE);
    buoyancyForce = std::make_shared<BuoyancyForceGenerator>(-13.);
    thermalForce = std::make_shared<ThermalLiftForceGenerator>(5000.);

    // Sistemas de partículas

    particleSystems.push_back(std::make_shared<ParticleSystem>());
    dustSystem = particleSystems.back();

    particleSystems.push_back(std::make_shared<ParticleSystem>());
    smokeSystem = particleSystems.back();

    // Agregacion de generadores a los sistemas

    sceneForceGeneratorsRegistry.insert(gravityForce);
    sceneForceGeneratorsRegistry.insert(buoyancyForce);

    smokeSystem->registerForceGenerator(gravityForce);
    smokeSystem->registerForceGenerator(thermalForce);

    dustSystem->registerForceGenerator(gravityForce);
    dustSystem->registerForceGenerator(buoyancyForce);
}

void 
GameplayScene::keyPress(unsigned char key) {
    switch (key) {

        case 'Q':

            gGenerateRigidbody = !gGenerateRigidbody;
            std::cout << "\n[LAS PARTICULAS SON: "
                << ((gGenerateRigidbody) ? "RIGIDBODYS": "NO RIGIDBODYS") << "]\n\n";

            break;

        case 'V': 
            if (canShoot) {

                canShoot = false;

                if (!shootWhite) {
                    std::shared_ptr<Entity> boliche = std::make_shared<Entity>(
                        GetCamera()->getDir().getNormalized() + GetCamera()->getEye(), 
                        bolicheGeometry, 
                        Vector4(1., 1., 1., 1.));

                    boliche->addComponent<ParticleComponent>(
                        std::make_unique<ProjectileParticleComponent>(GetCamera()->getDir().getNormalized(), 
                        Integrator::SYMPLECTIC_EULER , 100.0, 200., 40.));

                    boliche->addComponent<BolicheComponent>(
                        std::make_unique<BolicheComponent>(Vector3(0.), fieldRadius, -10., this)
                    );

                    boliche->addComponent<CubeAreaDeleterComponent>(deleteAreaComponent);

                    sceneEntities.addObject(boliche);

                    balls.addObject(boliche);
                }
                else {
                    Vector4 ballColor;

                    if (blueTurn) ballColor = Vector4(0., 0., 1., 1.);
                    else ballColor = Vector4(1., 0., 0., 1.);

                    std::shared_ptr<Entity> ball = std::make_shared<Entity>(
                        GetCamera()->getDir().getNormalized() + GetCamera()->getEye(), 
                        ballGeometry, 
                        ballColor);

                    ball->addComponent<DynamicRigidbodyComponent>(
                        std::make_unique<DynamicRigidbodyComponent>(*ball, myPhysxScene, 
                            GetCamera()->getDir().getNormalized() * 40., // velocidad lineal inicial
                            GetCamera()->getDir().getNormalized() * 15., //velocidad angular inicial
                            ballMass,
                            1., // friccion estatica
                            0.8, // friccion dinamica
                            0.1, // coeficiente de rebote
                            0.2, // damping lineal
                            0.3 // damping angular
                        ));

                    ball->addComponent<BallComponent>(
                        std::make_unique<BallComponent>(*ball, -13., this)
                    );
                    ball->addComponent<CubeAreaDeleterComponent>(deleteAreaComponent);

                    sceneEntities.addObject(ball);
                    balls.addObject(ball);

                    smokeSystem->addParticleGenerator(std::make_unique<SmokeFollowParticleGenerator>(
                        ball, // entidad que va a seguir
                        3., // offset vertical para generar la partícula
                        100., // altura donde las partículas se enfrian mas rápido
                        20., // altura donde las partículas se enfrían mas lento
                        10., // velocidad inicial mínima
                        20., // velocidad inicial máxima
                        PI/2., // angulo máximo de lanzamiento
                        6., // tiempo de vida de cada partícula
                        5., // tiempo de vida del generador
                        50., // generaciones mínimas por segundo
                        150., // generaciones máximas por segundo
                        particleGeometryHolder.any(),
                        myPhysxScene));
                }
            }
            
            break;
        
        case 'R': 

            std::cout << "\n ESCENA RESETEADA \n";
            
            balls.foreachAlive([](Entity& e) {e.kill();});
            balls.foreachAlive([](Entity& e) {});

            canShoot = true;
            shootWhite = false;
            blueTurn = true;

            break;
	}
}

void 
GameplayScene::bolicheOutOfBounds() {
    canShoot = true;

    std::cout << "\n [BOLICHE FUERA DE LIMITES, TIRA DE NUEVO] \n";
}

void 
GameplayScene::bolicheLanded(double x, double z) {
    canShoot = true;
    shootWhite = true;

    whiteBallPos = Vector3(x, -9.5, z);

    std::shared_ptr<Entity> boliche = std::make_shared<Entity>(
        whiteBallPos, 
        bolicheGeometry, 
        Vector4(1., 1., 1., 1.));

    sceneEntities.addObject(boliche);

    balls.addObject(boliche);

    balls.foreachAlive([](Entity&){});

    std::cout << "\n [TURNO DE AZUL] \n";
}

void 
GameplayScene::currentballOutOfBounds() {
    advanceRound();
}

void
GameplayScene::currentBallLanded(Vector3 pos) {
    if (blueTurn) {
        minDistanceBlue = std::min(minDistanceBlue, (whiteBallPos - pos).magnitude());
    }
    else {
        minDistanceRed = std::min(minDistanceRed, (whiteBallPos - pos).magnitude());
    }

    Vector4 ballColor;

    if (blueTurn) ballColor = Vector4(0., 0., 1., 1.);
    else ballColor = Vector4(1., 0., 0., 1.);

    std::shared_ptr<Entity> bola = std::make_shared<Entity>(
        pos, 
        ballGeometry, 
        ballColor);

    bola->addComponent<StaticRigidbodyComponent>(
        std::make_shared<StaticRigidbodyComponent>(*bola, myPhysxScene));

    sceneEntities.addObject(bola);
    balls.addObject(bola);

    balls.foreachAlive([](Entity&){});
    
    advanceRound();
}

void 
GameplayScene::onCollision(physx::PxActor* actor1, physx::PxActor* actor2) {

    Entity *ent1 = static_cast<Entity*>(actor1->userData);
    Entity *ent2 = static_cast<Entity*>(actor2->userData);

    bool    ball1 = ent1->hasComponent<BallComponent>(), 
            ball2 = ent2->hasComponent<BallComponent>(),
            floor1 = ent1->hasComponent<FloorComponent>(),
            floor2 = ent2->hasComponent<FloorComponent>();

    if ((ball1 && floor2) || (floor1 && ball2)) {

        BallComponent& ballComp = (ball1) ? ent1->getComponent<BallComponent>() : 
            ent2->getComponent<BallComponent>();

        if (!ballComp.hasImpacted()) {

            Vector3 pos = (ball1) ? ent1->getPos() : ent2->getPos();

            ballComp.floorImpact();

            dustSystem->addParticleGenerator(
                std::make_unique<DustDiskParticleGenerator>(
                    pos, 
                    5.5, // radio de disco
                    3., //min upward launch speed
                    5., // max upward launch speed 
                    0.6, // min particle duration 
                    1.3, // max particle duration
                    Vector4(1., 1., 0.0, 1.), // particle color
                    1., // generation duration 
                    100., // min tries per second
                    200., // max tries per second
                    particleGeometryHolder.any(),
                    myPhysxScene
                )
            );

            dustSystem->registerForceGenerator(std::make_shared<ExplosionForceGenerator>(
                addTimer(0.5), 
                pos, 
                6.5, 
                500.)
            );
        }
    }
}

void
GameplayScene::advanceRound() {

    if (blueTurn) { 

        std::cout << "\n [TURNO DE ROJO] \n";

        blueTurn = false; 
        canShoot = true;
    }
    else {
        if (++nRounds == maxRounds) {
            std::cout << " \n [FIN DE LA PARTIDA] \n\n";

            if (minDistanceBlue == minDistanceRed) {
                std::cout << " EMPATE \n";
            }
            else {
                
                std::cout << " GANADOR: ";

                if (minDistanceBlue < minDistanceBlue) {
                    std::cout << " AZUL\n\n";
                }
                else {
                    std::cout << " ROJO\n\n";
                }
            }

            std::cout << "Presiona (r/R) para reiniciar la partida...\n";
        } 
        else {
            blueTurn = true;
            std::cout << "\n [TURNO DE AZUL] \n";
            canShoot = true;
        }
    } 
}