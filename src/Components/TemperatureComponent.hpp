#pragma once

#include "Component.hpp"

class TemperatureComponent: public Component {
public:
    TemperatureComponent(Entity &e, double baseCooling, double heightCoolingFactor, 
        double coolingSaturationTopHeight, double coolingSaturationBottomHeight);
        
    void update(Entity& p, double t);
    double getTemperature();

private:
    double temperature, baseCooling, heightCoolingFactor, 
        coolingSaturationBottomHeight, coolingHeightArea;
};