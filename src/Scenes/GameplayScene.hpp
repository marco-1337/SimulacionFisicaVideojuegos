#pragma once

#include "Scene.hpp"

class GravityForceGenerator;
class BuoyancyForceGenerator;
class ThermalLiftForceGenerator;

class CubeAreaDeleterComponent;

class GameplayScene: public Scene {
public:
    GameplayScene();

    virtual void keyPress(unsigned char key) override;

    void bolicheOutOfBounds();
    void bolicheLanded(double x, double z);
    void currentballOutOfBounds();
    void currentBallLanded(Vector3 pos);
    virtual void onCollision(physx::PxActor* actor1, physx::PxActor* actor2) override;

private:
    void advanceRound();

// Parametros de generacion

    physx::PxGeometryHolder particleGeometryHolder;

    physx::PxSphereGeometry bolicheGeometry;
    physx::PxSphereGeometry ballGeometry;

    double particleMass, ballMass, fieldRadius;

    std::shared_ptr<CubeAreaDeleterComponent> deleteAreaComponent = nullptr;

    std::shared_ptr<ParticleSystem> smokeSystem = nullptr;
    std::shared_ptr<ParticleSystem> dustSystem = nullptr;
    
    std::shared_ptr<GravityForceGenerator> gravityForce = nullptr;
    std::shared_ptr<ThermalLiftForceGenerator> thermalForce = nullptr;
    std::shared_ptr<BuoyancyForceGenerator> buoyancyForce = nullptr;

    KillableList<Entity> balls;


// Logica del juego

    float minDistanceRed, minDistanceBlue;

    Vector3 whiteBallPos;

    // Shoot white es para saber si ha sido disparada o no
    // blueTurn = false = roja, blueTurn = true = azul
    bool canShoot, shootWhite, blueTurn;

    int nRounds, maxRounds;
};