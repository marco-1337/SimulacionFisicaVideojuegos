#include "ParticleComponent.hpp"

class ProjectileParticleComponent: public ParticleComponent {
public:
    ProjectileParticleComponent(const Vector3& shootDirection, Integrator integrator, double mass, double speed, 
        double simulatedSpeed);

    virtual double getMass() const override;

protected:
    double simulatedMass;
};