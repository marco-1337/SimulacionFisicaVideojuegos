#pragma once

#include <cstdint>
#include "mpl.h"

// Components list - must have at least one element
//
class ParticleComponent;
class HeightDeletableComponent;
class TimeDeletableComponent;
class StaticRigidbodyComponent;
class DynamicRigidbodyComponent;
class TemperatureComponent;

#define _CMPS_LIST_ \
	ParticleComponent, \
	HeightDeletableComponent, \
	TimeDeletableComponent, \
	StaticRigidbodyComponent, \
	DynamicRigidbodyComponent, \
	TemperatureComponent


namespace cmp {
using cmpList = mpl::TypeList<_CMPS_LIST_>;
}

using cmpId_t = uint8_t;
constexpr cmpId_t maxComponentId = cmp::cmpList::size;

template<typename T>
constexpr cmpId_t cmpId = mpl::IndexOf<T, cmp::cmpList>();