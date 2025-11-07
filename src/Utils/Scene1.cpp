#include "Scene1.hpp"

#include "Particle.hpp"
#include "Projectile.hpp"
#include "RenderUtils.hpp"
#include "EntityContainer.hpp"

using namespace physx;

Scene1::Scene1(): Scene() {

    PxSphereGeometry geometry = PxSphereGeometry(0.5f);
	particleShape = CreateShape(geometry);

    sceneEntities->addEntity(new Entity(Vector3(0., 0., 0), particleShape, Vector4(1.)));

    sceneEntities->addEntity(new Entity(Vector3(10., 0., 0), particleShape, Vector4(1., 0., 0., 1.)));
    sceneEntities->addEntity(new Entity(Vector3(5., 0., 0), particleShape, Vector4(1., 0., 0., 1.)));

    sceneEntities->addEntity(new Entity(Vector3(0., 10., 0), particleShape, Vector4(0., 1., 0., 1.)));
    sceneEntities->addEntity(new Entity(Vector3(0., 5., 0), particleShape, Vector4(0., 1., 0., 1.)));

    sceneEntities->addEntity(new Entity(Vector3(0., 0., 10.), particleShape, Vector4(0., 0., 1., 1.)));
    sceneEntities->addEntity(new Entity(Vector3(0., 0., 5.), particleShape, Vector4(0., 0., 1., 1.)));
}

Scene1::~Scene1() {
    particleShape->release();
}

void 
Scene1::keyPress(unsigned char key) {

    switch(key) {
        case 'I':
            sceneEntities->addEntity(new Particle(Vector3(0.0), particleShape, Vector4(1., 0., 0., 1.), 
                Vector3(2.0, 2.0, -1.0)*10., Integrator::EULER, 1., 5.));
            break;
        case 'O':
            sceneEntities->addEntity(new Particle(Vector3(0.0), particleShape, Vector4(0., 1., 0., 1.),
                Vector3(2.0, 2.0, -1.0)*10., Integrator::SYMPLECTIC_EULER, 100., 5.));
            break;
        /*
        case 'P':
            sceneEntities->addEntity(new Particle(Vector3(0.0), particleShape, Vector4(0., 0., 1., 1.), Vector3(2.0, 2.0, -1.0)*10., 
                Vector3(0.0, -9.0, 0.0), Integrator::VERLET));
            break;
        */
        case  'F':
            sceneEntities->addEntity(new Projectile(GetCamera()->getEye(), particleShape, Vector4(1., 1., 0., 1.), 
                Integrator::SYMPLECTIC_EULER, 10., 10., GetCamera()->getDir(), 200., 50.));
            break;

        // Para testear los arcos
        case  'G':
            sceneEntities->addEntity(new Projectile(Vector3(0.0), particleShape, Vector4(0., 1., 1., 1.), 
                Integrator::SYMPLECTIC_EULER, 10., 100., Vector3(2., 2., -1.), 100., 50.));
            break;
        case  'H':
            sceneEntities->addEntity(new Projectile(Vector3(0.0), particleShape, Vector4(1., 0.5, 0.5, 1.), 
                Integrator::SYMPLECTIC_EULER, 10., 100., Vector3(2., 2., -1.), 100., 25.));
            break;
        default:
            break;
    }
}

