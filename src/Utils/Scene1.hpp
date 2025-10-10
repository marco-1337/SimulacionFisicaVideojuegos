#include "Scene.hpp"

namespace physx {
    class PxShape;
}

class Scene1: public Scene {
public:
    Scene1();
    ~Scene1();

    void keyPress(unsigned char key) override;
private:
    physx::PxShape *particleShape;
};