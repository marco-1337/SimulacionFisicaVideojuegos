#pragma once

#include "Scene.hpp"

class GravityForceGenerator;
class BuoyancyForceGenerator;

class Scene2: public Scene {
public:
    Scene2();

    virtual void keyPress(unsigned char key) override;
private:
    physx::PxSphereGeometry particleGeometry;

    std::shared_ptr<ParticleSystem> smokeSystem = nullptr;
    
    std::shared_ptr<GravityForceGenerator> gravityForce = nullptr;
    std::shared_ptr<BuoyancyForceGenerator> buoyancyForce = nullptr;
};