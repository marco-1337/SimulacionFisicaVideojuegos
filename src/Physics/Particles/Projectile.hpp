#include "Particle.hpp"

class Projectile: public Particle {
public:
    Projectile(Vector3 position, Shape *shape, Vector4 color, Integrator integrator, double timeToDie, 
        double mass, Vector3 shootDirection, double speed, double simulatedSpeed);

    inline virtual double getMass() const override { return mass/simulatedMass; }

protected:
    double simulatedMass;
};