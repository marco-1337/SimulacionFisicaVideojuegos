#include "Scene1.hpp"
#include "Particle.hpp"
#include "RenderUtils.hpp"

using namespace physx;

Scene1::Scene1() {
	PxSphereGeometry particleGeometry = PxSphereGeometry(1.0f);
	particleShape = CreateShape(particleGeometry);
}

Scene1::~Scene1() {
    particleShape->release();
}

void 
Scene1::keyPress(unsigned char key) {
    switch(key) {
        case 'I':
            entities.push_back(new Particle(Vector3(0.0), particleShape, Vector4(1., 0., 0., 1.), Vector3(10.0, 10.0, -5.0),
                Vector3(0.0, -9.0, 0.0), Integrator::EULER));
            break;
        case 'O':
            entities.push_back(new Particle(Vector3(0.0), particleShape, Vector4(0., 1., 0., 1.), Vector3(10.0, 10.0, -5.0), 
                Vector3(0.0, -9.0, 0.0), Integrator::SYMPLECTIC_EULER));
            break;
        case 'P':
            entities.push_back(new Particle(Vector3(0.0), particleShape, Vector4(0., 0., 1., 1.), Vector3(10.0, 10.0, -5.0), 
                Vector3(0.0, -9.0, 0.0), Integrator::VERLET));
            break;
    }
}

