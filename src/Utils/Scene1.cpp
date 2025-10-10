#include "Scene1.hpp"
#include "Particle.hpp"
#include "Projectile.hpp"
#include "RenderUtils.hpp"

using namespace physx;

Scene1::Scene1() {

    PxSphereGeometry geometry = PxSphereGeometry(0.5f);
	PxShape *shape = CreateShape(geometry);

    entities.push_back(new Particle(Vector3(0., 0., 0), shape, Vector4(1.), Vector3(0.), Vector3(0.), 
        Integrator::EULER, 1., 0., false));

    entities.push_back(new Particle(Vector3(10., 0., 0), shape, Vector4(1., 0., 0., 1.), Vector3(0.), Vector3(0.), 
        Integrator::EULER, 1., 0., false));
    entities.push_back(new Particle(Vector3(5., 0., 0), shape, Vector4(1., 0., 0., 1.), Vector3(0.), Vector3(0.), 
        Integrator::EULER, 1., 0., false));

    entities.push_back(new Particle(Vector3(0., 10., 0), shape, Vector4(0., 1., 0., 1.), Vector3(0.), Vector3(0.), 
        Integrator::EULER, 1., 0., false));
    entities.push_back(new Particle(Vector3(0., 5., 0), shape, Vector4(0., 1., 0., 1.), Vector3(0.), Vector3(0.), 
        Integrator::EULER, 1., 0., false));

    entities.push_back(new Particle(Vector3(0., 0., 10.), shape, Vector4(0., 0., 1., 1.), Vector3(0.), Vector3(0.), 
        Integrator::EULER, 1., 0., false));
    entities.push_back(new Particle(Vector3(0., 0., 5.), shape, Vector4(0., 0., 1., 1.), Vector3(0.), Vector3(0.), 
        Integrator::EULER, 1., 0., false));

    shape->release();

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
            entities.push_back(new Particle(Vector3(0.0), particleShape, Vector4(1., 0., 0., 1.), Vector3(2.0, 2.0, -1.0)*10.,
                Vector3(0.0, -9.0, 0.0), Integrator::EULER));
            break;
        case 'O':
            entities.push_back(new Particle(Vector3(0.0), particleShape, Vector4(0., 1., 0., 1.), Vector3(2.0, 2.0, -1.0)*10., 
                Vector3(0.0, -9.0, 0.0), Integrator::SYMPLECTIC_EULER));
            break;
        case 'P':
            entities.push_back(new Particle(Vector3(0.0), particleShape, Vector4(0., 0., 1., 1.), Vector3(2.0, 2.0, -1.0)*10., 
                Vector3(0.0, -9.0, 0.0), Integrator::VERLET));
            break;
        case  'F':
            entities.push_back(new Projectile(GetCamera()->getEye(), particleShape, Vector4(1., 1., 0., 1.), 
                Integrator::SYMPLECTIC_EULER, 0.99, 5., 10., GetCamera()->getDir(), 200., 50.));
            break;

        // Para testear los arcos
        case  'G':
            entities.push_back(new Projectile(Vector3(0.0), particleShape, Vector4(0., 1., 1., 1.), 
                Integrator::SYMPLECTIC_EULER, 0.99, 10., 100., Vector3(2., 2., -1.), 20., 20.));
            break;
        case  'H':
            entities.push_back(new Projectile(Vector3(0.0), particleShape, Vector4(1., 0.5, 0.5, 1.), 
                Integrator::SYMPLECTIC_EULER, 0.99, 20., 100., Vector3(2., 2., -1.), 20., 10.));
            break;
        default:
            break;
    }
}

