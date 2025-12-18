#pragma once

#include "Scene.hpp"

class GravityForceGenerator;

class Scene1: public Scene {
public:
    Scene1();
    
    virtual void keyPress(unsigned char key) override;
private:
    physx::PxSphereGeometry particleGeometry;
    std::shared_ptr<ParticleSystem> dustSystem = nullptr;
    
    std::shared_ptr<GravityForceGenerator> gravityForce = nullptr;

};