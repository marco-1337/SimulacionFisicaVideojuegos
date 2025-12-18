#pragma once

#include "Killable.hpp"
#include "Component.hpp"
#include "components_defs.hpp"

#include <cassert>

#include <memory>

#include "physxDefs.hpp"

class RenderItem;

class Entity: public Killable {
public:
    Entity(const Vector3& position, const physx::PxGeometry& geometry, Vector4 color);
    ~Entity();

    void update(double t);
    void enableRender();

    template<typename T>
	inline void addComponent(std::shared_ptr<T> component) {

        static_assert(std::is_base_of_v<Component, T>, "T debe heredar de Component");

		constexpr cmpId_t cId = cmpId<T>;
		assert(cId < maxComponentId);
		components[cId] = component;
	}

    template <typename T>
    inline bool hasComponent() const {
        constexpr cmpId_t cId = cmpId<T>;
		assert(cId < maxComponentId);

		return components[cId] != nullptr;
    }

    template <typename T>
    inline T& getComponent() const {
        constexpr cmpId_t cId = cmpId<T>;
		assert(cId < maxComponentId);

		return static_cast<T&>(*(components[cId]));
    }

    Vector3 getPos() const;
    void setPos(Vector3 pos);
    void translate(Vector3 pos);

    double getBoundsHeight();
    double getApproximatedVolume();

    void setColor(Vector4 color);
    void addActorToRenderItem(physx::PxRigidActor *actor);

protected:

    friend class StaticRigidbodyComponent;
    friend class DynamicRigidbodyComponent;

    std::shared_ptr<Component> components[maxComponentId] = {};
    
    RenderItem *myRenderItem = nullptr;
    Shape *myShape = nullptr;
    physx::PxTransform *myTransform = nullptr;
    physx::PxRigidActor *myActor = nullptr;
};