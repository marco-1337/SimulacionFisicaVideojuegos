#include "ThermalLiftForceGenerator.hpp"

#include "TemperatureComponent.hpp"
#include "ParticleComponent.hpp"
#include "DynamicRigidbodyComponent.hpp"

ThermalLiftForceGenerator::ThermalLiftForceGenerator(double thermalLiftCoeficient)
:thermalLiftCoeficient(thermalLiftCoeficient) {}

void 
ThermalLiftForceGenerator::tryAddForce(Entity& ent, double dt) {

    if (ent.hasComponent<TemperatureComponent>()) {

        float thermalLift = thermalLiftCoeficient * ent.getComponent<TemperatureComponent>().getTemperature();

        if (ent.hasComponent<ParticleComponent>()) {
            ent.getComponent<ParticleComponent>().addForce(Vector3(0., thermalLift, 0.));
        }

        if (ent.hasComponent<DynamicRigidbodyComponent>()) {
            ent.getComponent<DynamicRigidbodyComponent>().addForceAtCenterOfMass(Vector3(0., thermalLift, 0.));
        }
    }
}