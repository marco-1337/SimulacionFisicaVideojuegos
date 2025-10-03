#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"

#include <iostream>

#include "Particle.h"
#include <list>

std::string display_text = "This is a test";


using namespace physx;

PxDefaultAllocator		gAllocator;
PxDefaultErrorCallback	gErrorCallback;

PxFoundation*			gFoundation = NULL;
PxPhysics*				gPhysics	= NULL;


PxMaterial*				gMaterial	= NULL;

PxPvd*                  gPvd        = NULL;

PxDefaultCpuDispatcher*	gDispatcher = NULL;
PxScene*				gScene      = NULL;
ContactReportCallback gContactReportCallback;

std::vector<RenderItem*> gAxis = std::vector<RenderItem*>(); 
std::list<Particle*> gParticles = std::list<Particle*>();

// Initialize physics engine
void initPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	gFoundation = PxCreateFoundation(PX_FOUNDATION_VERSION, gAllocator, gErrorCallback);

	gPvd = PxCreatePvd(*gFoundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	gPvd->connect(*transport,PxPvdInstrumentationFlag::eALL);

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(),true,gPvd);

	gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	// For Solid Rigids +++++++++++++++++++++++++++++++++++++
	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.8f, 0.0f);
	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = contactReportFilterShader;
	sceneDesc.simulationEventCallback = &gContactReportCallback;
	gScene = gPhysics->createScene(sceneDesc);

	// Esfera central

	PxTransform *_transform = new PxTransform(PxVec3(0., 0., 0.));
	PxSphereGeometry _geometry = PxSphereGeometry(1.0f);
	PxShape *_shape = CreateShape(_geometry);

	RenderItem *_item = new RenderItem(_shape, _transform, PxVec4(1., 1., 1., 1.));
	gAxis.push_back(_item);

	_transform = new PxTransform(PxVec3(10., 0., 0.));
	_item = new RenderItem(_shape, _transform, PxVec4(1., 0., 0., 1.));
	gAxis.push_back(_item);

	_transform = new PxTransform(PxVec3(0., 10., 0.));
	_item = new RenderItem(_shape, _transform, PxVec4(0., 1., 0., 1.));
	gAxis.push_back(_item);
	
	_transform = new PxTransform(PxVec3(0., 0., 10.));
	_item = new RenderItem(_shape, _transform, PxVec4(0., 0., 1., 1.));
	gAxis.push_back(_item);
}


// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	for (std::list<Particle*>::iterator it = gParticles.begin(); it != gParticles.end();) {
		
		(*it)->integrate(t);

		if ((*it)->isDead()) {
			Particle *aux = *it;
			it = gParticles.erase(it);
			delete aux;
		} else ++it;
	}

	PX_UNUSED(interactive);

	gScene->simulate(t);
	gScene->fetchResults(true);
}

// Function to clean data
// Add custom code to the begining of the function
void cleanupPhysics(bool interactive)
{
	for(auto elem : gAxis) {
		DeregisterRenderItem(elem);
		delete elem;
	}

	for(auto particle : gParticles) {
		delete particle;
	}

	PX_UNUSED(interactive);

	// Rigid Body ++++++++++++++++++++++++++++++++++++++++++
	gScene->release();
	gDispatcher->release();
	// -----------------------------------------------------
	gPhysics->release();	
	PxPvdTransport* transport = gPvd->getTransport();
	gPvd->release();
	transport->release();
	
	gFoundation->release();
}

// Function called when a key is pressed
void keyPress(unsigned char key, const PxTransform& camera)
{
	PX_UNUSED(camera);

	switch(toupper(key))
	{
	//case 'B': break;
	//case ' ':	break;
	
	case 'I':
		gParticles.push_back(new Particle(Vector3(0.0), Vector3(10.0, 10.0, -5.0), Vector3(0.0, -9.0, 0.0), Particle::Integrator::EULER));
		break;
	case 'O':
		gParticles.push_back(new Particle(Vector3(0.0), Vector3(10.0, 10.0, -5.0), Vector3(0.0, -9.0, 0.0), Particle::Integrator::SYMPLECTIC_EULER));
		break;
	case 'P':
		gParticles.push_back(new Particle(Vector3(0.0), Vector3(10.0, 10.0, -5.0), Vector3(0.0, -9.0, 0.0), Particle::Integrator::VERLET));
		break;
	case ' ':
	{
		break;
	}
	default:
		break;
	}
}

void onCollision(physx::PxActor* actor1, physx::PxActor* actor2)
{
	PX_UNUSED(actor1);
	PX_UNUSED(actor2);
}


int main(int, const char*const*)
{
#ifndef OFFLINE_EXECUTION 
	extern void renderLoop();
	renderLoop();
#else
	static const PxU32 frameCount = 100;
	initPhysics(false);
	for(PxU32 i=0; i<frameCount; i++)
		stepPhysics(false);
	cleanupPhysics(false);
#endif

	return 0;
}