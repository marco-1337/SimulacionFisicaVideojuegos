#include "Scene.hpp"

class ParticleSystem;

class Scene2: public Scene {
public:
    Scene2();
    ~Scene2();

    void keyPress(unsigned char key) override;
    void update(double dt) override;

private:
    std::shared_ptr<ParticleSystem> pSystem;
};