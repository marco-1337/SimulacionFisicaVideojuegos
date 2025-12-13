#pragma once

#include "Killable.hpp"
#include "Component.hpp"
#include "components_defs.hpp"

#include <cassert>

#include <memory>

#include "physxDefs.hpp"

class RenderItem;

static constexpr double PI = 3.14159265358979323846;
static constexpr double GRAVITY = -9.8;

class Entity: public Killable {
public:
    Entity(Vector3 position, Shape *shape, Vector4 color);
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

    Vector3 getPos() const;
    void setPos(Vector3 pos);
    void translate(Vector3 pos);

protected:
    std::shared_ptr<Component> components[maxComponentId] = {};
    
    RenderItem *myRenderItem;
    physx::PxTransform myTransform;

    friend class Component;
};