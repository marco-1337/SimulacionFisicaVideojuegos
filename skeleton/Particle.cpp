#include "Particle.h"
#include "RenderUtils.hpp"

#include <iostream>
#include <cmath>

using namespace physx;

Particle::Particle(Vector3 pos, Vector3 vel, Vector3 accel, Integrator integrator, double dampingVal, double timeToDie)
: vel(vel), 
accel(accel),
integrator(integrator),
dampingVal(dampingVal),
timeToDie(timeToDie),
aliveTime(0.) {

    pose = PxTransform(pos);
	PxSphereGeometry _geometry = PxSphereGeometry(1.0f);
	PxShape *shape = CreateShape(_geometry);

    Vector4 color = Vector4(0.);
    color.w = 1.;
    
    switch (integrator) {
        case EULER: color.x = 1.; break;
        case SYMPLECTIC_EULER: color.y = 1.; break;
        case VERLET: color.z = 1.; break;
    }

    renderItem = new RenderItem(shape, &pose, color);
    
    if (integrator == VERLET) this->integrator = PRE_VERLET;
}

Particle::~Particle() {
    DeregisterRenderItem(renderItem);
    delete renderItem;
}

void
Particle::integrate(double t) {

    aliveTime += t;

    switch (integrator) {
        case EULER:

            pose.p += vel * t;
            vel += accel * t;

            // Damping
            vel *= std::pow(dampingVal, t);

            break;
        
        case SYMPLECTIC_EULER:

            vel += accel * t;
            pose.p += vel * t;

            // Damping
            vel *= std::pow(dampingVal, t);
            
            break;
        
        case VERLET:

            currPos = pose.p;
            pose.p = 2.0 * pose.p - prevPos + accel * t * t;
            prevPos = currPos;

            break;
        
        case PRE_VERLET:
            
            prevPos = pose.p;
            vel += accel * t;
            pose.p += vel * t;

            integrator = VERLET;

            break;
    }
}

bool
Particle::isDead(){
    return aliveTime > timeToDie;
}