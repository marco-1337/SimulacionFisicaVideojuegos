#include "Scene0.hpp"

#include "Particle.hpp"
#include "RenderUtils.hpp"

using namespace physx;

Scene0::Scene0() {

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
}

Scene0::~Scene0() {}