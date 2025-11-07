#include "Scene.hpp"

#include <queue>

class ParticleSystem;

namespace physx {
    class PxShape;
}

class GameScene: public Scene {
public:
    GameScene();
    ~GameScene();

    void keyPress(unsigned char key) override;
    void update(double dt) override;

    void landed(Vector3 pos);

private:
    bool canShoot = true;

    Vector3 whiteBallPos;

    Vector4 playerAColor;
    Vector4 playerBColor;

    Vector3 planeCentre;
    double planeExtension, verticalLimit;   

    int ATurns = 3;
    int BTurns = 3;

    Vector3 ballCentre;
    physx::PxShape *ballShape;

    std::shared_ptr<ParticleSystem> dustParticleSystem;
    double minDistance = -1.;
    char winner = '-';
};