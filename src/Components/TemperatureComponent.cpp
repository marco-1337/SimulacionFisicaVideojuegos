#pragma once

#include "TemperatureComponent.hpp"

#include "ParticleComponent.hpp"
#include "Entity.hpp"

#include <algorithm>
#include <cmath>

TemperatureComponent::TemperatureComponent(Entity &e, double baseCooling, double heightCoolingFactor, 
        double coolingSaturationTopHeight, double coolingSaturationBottomHeight)
: coolingSaturationBottomHeight(coolingSaturationBottomHeight),
coolingHeightArea(std::max((coolingSaturationTopHeight - coolingSaturationBottomHeight), 0.)),
baseCooling(std::clamp(baseCooling, 0., 1.)),
heightCoolingFactor(std::clamp(heightCoolingFactor, 0., 1.)) {

    this->temperature = 1.;
    e.setColor(Vector4(0., 1., 0., 1.));
}

void
TemperatureComponent::update(Entity &e, double dt) {

    double height = std::clamp(
        std::max(e.getPos().y - coolingSaturationBottomHeight, 0.) / coolingHeightArea, 
        0., 
        1.0
    );

    double coolingRate = baseCooling + ( height * heightCoolingFactor);
    temperature = std::max(temperature - (coolingRate * dt), 0.);
    e.setColor(Vector4(0.5*temperature, 0.5*temperature, 0.5*temperature, 0.5));
}

double
TemperatureComponent::getTemperature() { return temperature; }