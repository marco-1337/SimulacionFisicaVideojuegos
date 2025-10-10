#include "Particle.hpp"

class Projectile: public Particle {
public:
    Projectile(Vector3 position, Shape *shape, Vector4 color, Integrator integrator, 
        double damping, double timeToDie, double mass, Vector3 shootDirection, 
        double speed, double simulatedSpeed);

protected:
    void calculateGravity();

    double mass, simulatedMass;
    double speed, simulatedSpeed;
};