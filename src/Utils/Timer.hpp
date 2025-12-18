#pragma once

#include "Killable.hpp"

#include <cmath>
#include <memory>

class Scene;

class Timer: public Killable {
private:
    Timer(double time): time(std::max(0., time)) {}

    static std::shared_ptr<Timer> Create(double time) {
        return std::shared_ptr<Timer>(new Timer(time));
    }

    double currTime = 0.;
    double time;

    friend class Scene;
public:

    void addTime(double t) { 
        currTime += t;
        if (currTime >= time) alive = false;
    }

    double getCurrentTime() { return currTime; }

    double getTotalTime() { return time; }

};